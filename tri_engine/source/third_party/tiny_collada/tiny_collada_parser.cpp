//  mcp_parser.cpp

#include "tiny_collada_parser.hpp"
#include "tinyxml2.h"
#include <cassert>

#if 1
    #define TINY_COLLADA_DEBUG  1
#else
    #define TYNE_COLLADA_DEBUG  0
#endif


#if TINY_COLLADA_DEBUG
    #define TINY_COLLADA_TRACE(...)         ::std::printf(__VA_ARGS__)
    #define TINY_COLLADA_ASSERT(exp)        assert(exp)
#else

    #define TINY_COLLADA_TRACE(...)         (void)0
    #define TINY_COLLADA_ASSERT(exp)        (void)0
#endif



namespace {

constexpr int PARSE_STRING_SIZE = 64;

const char* INPUT_NODE_NAME = "input";
const char* SOURCE_NODE_NAME = "source";
const char* SEMANTIC_ATTR_NAME = "semantic";
const char* MESH_NODE_NAME = "mesh";
const char* GEOMETRY_NODE_NAME = "geometry";
const char* INDEX_NODE_NAME = "p";
const char* STRIDE_ATTR_NAME = "stride";
const char* ACCESSOR_NODE_NAME = "accessor";
const char* TECH_COMMON_NODE_NAME = "technique_common";
const char* LIB_GEOMETRY_NODE_NAME = "library_geometries";
const char* ID_ATTR_NAME = "id";
const char* OFFSET_ATTR_NAME = "offset";
const char* VERTICES_NODE_NAME = "vertices";
const char* COUNT_ATTR_NAME = "count";


void parseEffect(
    std::shared_ptr<tinycollada::ColladaMaterial>& material,
    const tinyxml2::XMLElement* shading
);


//----------------------------------------------------------------------
//  child elementを取得する
//  大文字小文字がバージョンによってバラバラな場合はここで吸収する
const tinyxml2::XMLElement* firstChildElement(
    const tinyxml2::XMLElement* parent,
    const char* const child_name
) {
    TINY_COLLADA_ASSERT(parent);
    const tinyxml2::XMLElement* child = parent->FirstChildElement(child_name);
    return child;
}

//----------------------------------------------------------------------
//  attributeを取得する
//  大文字小文字がバージョンによってバラバラな場合はここで吸収する
const char* getElementAttribute(
    const tinyxml2::XMLElement* element,
    const char* const attri_name
) {
    TINY_COLLADA_ASSERT(element);
    return element->Attribute(attri_name);
}


//======================================================================
struct PrimitiveSelector
{
    const char* name_;
    tinycollada::ColladaMesh::PrimitiveType type_;
};

#define PRIMITIVE_TYPE_NUM 2
const PrimitiveSelector PRIMITIVE_TYPE_SELECT[PRIMITIVE_TYPE_NUM] = {
    {"triangles", tinycollada::ColladaMesh::PRIMITIVE_TRIANGLES},
    {"polylist", tinycollada::ColladaMesh::PRIMITIVE_TRIANGLES}
};




//======================================================================
//  visual_sceneノードデータ
struct VisualSceneData
{
    VisualSceneData()
        : type_(TYPE_UNKNOWN)
        , url_(nullptr)
        , matrix_()
        , bind_material_(nullptr)
    {}


    void dump() {
        TINY_COLLADA_TRACE("VisualSceneNode:type = %d ", type_);
        if (url_) {
            TINY_COLLADA_TRACE("url = %s ", url_);
        }
        if (bind_material_) {
            TINY_COLLADA_TRACE("bind_material = %s", bind_material_);
        }
        TINY_COLLADA_TRACE(" matrix (%lu)", matrix_.size());
        for (int i = 0; i < matrix_.size(); ++i) {
            if ((i % 4) == 0) {
                TINY_COLLADA_TRACE("\n");
            }
            TINY_COLLADA_TRACE(" %f", matrix_[i]);
        }
        TINY_COLLADA_TRACE("\n");
    }

    enum Type {
        TYPE_GEOMETRY,
        TYPE_UNKNOWN,
    };
    Type type_;
    const char* url_;
    std::vector<float> matrix_;
    const char* bind_material_;
};
using VisualScenes = std::vector<std::shared_ptr<VisualSceneData>>;


//======================================================================
//  material
struct MaterialData
{
    const char* id_;
    const char* url_;
    
    void dump() {
        TINY_COLLADA_TRACE("MaterialData:id %s  url %s\n", id_, url_);
    }
};
using Materials = std::vector<std::shared_ptr<MaterialData>>;


//======================================================================
//  material effect
struct EffectData
{
    struct Surface {

        Surface()
            : sid_(nullptr)
            , init_from_(nullptr)
        {}


        void setupSurface(
            const char* const sid,
            const tinyxml2::XMLElement* surface
        ) {
            sid_ = sid;
            const tinyxml2::XMLElement* init_from = firstChildElement(surface, "init_from");
            init_from_ = init_from->GetText();
        }

        void dump() const {
            printf("Surface:");
            if (sid_) {
                printf("sid = %s", sid_);
            }
            if (init_from_) {
                printf ("init from %s", init_from_);
            }
            printf("\n");
        }

        const char* sid_;
        const char* init_from_;
    };

    struct Sampler2D {

        Sampler2D()
            : sid_(nullptr)
            , source_(nullptr)
            , min_filter_(nullptr)
            , mag_filter_(nullptr)
        {}


        void setupSampler2D(
            const char* const sid,
            const tinyxml2::XMLElement* sampler2d
        ) {
            //  sid
            sid_ = sid;


            //  source
            const tinyxml2::XMLElement* source = firstChildElement(sampler2d, "source");
            if (source) {
                source_ = source->GetText();
            }

            //  min filter
            const tinyxml2::XMLElement* min_filter = firstChildElement(sampler2d, "minfilter");
            if (min_filter) {
                min_filter_ = min_filter->GetText();
            }

            //  mag filter
            const tinyxml2::XMLElement* mag_filter = firstChildElement(sampler2d, "magfilter");
            if (mag_filter) {
                mag_filter_ = mag_filter->GetText();
            }


        }

        void dump() const {
            TINY_COLLADA_TRACE("Sampler2D: sid = %s  source = %s  minfil = %s  magfil = %s\n", sid_, source_, min_filter_, mag_filter_);
        }

        const char* sid_;
        const char* source_;
        const char* min_filter_;
        const char* mag_filter_;
    };

    void setupEffectData(
        const tinyxml2::XMLElement* effect
    ) {
        const char* SHADING_NAME[3] = {
            "blinn",
            "phong",
            "----"
        };

        //  id
        id_ = getElementAttribute(effect, "id");
          
              
        const tinyxml2::XMLElement* profile_common = firstChildElement(effect, "profile_COMMON");
            
        //  マテリアルデータ取得
        const tinyxml2::XMLElement* technique = firstChildElement(profile_common, "technique");

        material_ = std::make_shared<tinycollada::ColladaMaterial>();
        id_ = getElementAttribute(effect, "id");

        for (int shade_idx = 0; shade_idx < 3; ++shade_idx) {
            const tinyxml2::XMLElement* shading = firstChildElement(technique, SHADING_NAME[shade_idx]);
            if (shading) {
                //  シェーディング
                material_->shading_name_ = SHADING_NAME[shade_idx];
                parseEffect(material_, shading);
                break;
            }
        }

        //  newparam
        const tinyxml2::XMLElement* newparam = firstChildElement(profile_common, "newparam");

        while (newparam) {
            const char* sid = getElementAttribute(newparam, "sid");
            const tinyxml2::XMLElement* surface = firstChildElement(newparam, "surface");
            const tinyxml2::XMLElement* sampler2d = firstChildElement(newparam, "sampler2D");
            if (surface) {
                surface_ = std::make_shared<Surface>();
                surface_->setupSurface(sid, surface);
            }
            else if (sampler2d) {
                sampler2d_ = std::make_shared<Sampler2D>();
                sampler2d_->setupSampler2D(sid, sampler2d);
            }

            newparam = newparam->NextSiblingElement("newparam");
        }
    }

    void dump() {
        TINY_COLLADA_TRACE("EffectData: id = %s\n", id_);
        if (material_) {
            material_->dump();
        }
        if (sampler2d_) {
            sampler2d_->dump();
        }
        if (surface_) {
            surface_->dump();
        }
    }
    EffectData()
        : id_(nullptr)
        , material_(nullptr)
        , sampler2d_(nullptr)
        , surface_(nullptr)
    {}


    const char* id_;
    std::shared_ptr<tinycollada::ColladaMaterial> material_;
    std::shared_ptr<Sampler2D> sampler2d_;
    std::shared_ptr<Surface> surface_;
};
using Effects = std::vector<std::shared_ptr<EffectData>>;


//======================================================================
//  textures
struct ImageData
{
    void dump() {
        TINY_COLLADA_TRACE("ImageData: id = %s  init_from = %s\n", id_, init_from_);
    }

    ImageData()
        : id_(nullptr)
        , init_from_(nullptr)
    {}

    const char* id_;
    const char* init_from_;
};
using Images = std::vector<std::shared_ptr<ImageData>>;


//======================================================================
//  インプットデータ
struct InputData
{
    InputData()
        : semantic_(nullptr)
        , source_(nullptr)
        , offset_(0)
    {}
    
    void dump() {
        TINY_COLLADA_TRACE("InputData:semantic = ");
        if (semantic_) {
            printf("%s", semantic_);
        }
        TINY_COLLADA_TRACE("  source = ");
        if (source_) {
            printf("%s", source_);
        }
        TINY_COLLADA_TRACE("  offset = %d\n", offset_);
    }
    
    const char* semantic_;
    const char* source_;
    int offset_;
};
    
//======================================================================
//  ソースデータ
struct SourceData
{
    SourceData()
        : id_(nullptr)
        , stride_(0)
        , data_()
        , input_(nullptr)
    {}
    
    void dump() {
        TINY_COLLADA_TRACE("SourceData:id = %s  stride = %d\n", id_, stride_);
    }
    
    const char* id_;
    uint32_t stride_;
    std::vector<float> data_;
    InputData* input_;
};



//======================================================================
//  メッシュ情報
struct MeshInformation {

    //----------------------------------------------------------------------
    //  指定idのinputを探す
    InputData* searchInputBySource(
        const char* const id
    ) {
        for (int i = 0; i < inputs_.size(); ++i) {
            InputData* input = &inputs_[i];
            TINY_COLLADA_TRACE("search %s == %s\n", id, input->source_);
            if (std::strncmp(input->source_, id, PARSE_STRING_SIZE) == 0){
                return input;
            }
        }
        return nullptr;
    }


    //----------------------------------------------------------------------
    //  指定semanticのsourceを探す
    SourceData* searchSourceBySemantic(
        const char* const semantic
    ) {
        size_t sources_size = sources_.size();
        TINY_COLLADA_TRACE("\nsearchSourceBySemantic %s %lu\n", semantic, sources_size);
        for (int i = 0; i < sources_size; ++i) {
            SourceData* source = &sources_[i];
            InputData* input = source->input_;
            if (!input) {
                TINY_COLLADA_TRACE("no input - %s\n", source->id_);
                continue;
            }
            TINY_COLLADA_TRACE("  %s %s\n", input->semantic_, input->source_);   
            if (std::strncmp(input->semantic_, semantic, PARSE_STRING_SIZE) == 0) {
                TINY_COLLADA_TRACE("%s - %s [%s] FOUND.\n", __FUNCTION__, semantic, input->source_);
                return source;
            }
        }
        TINY_COLLADA_TRACE("%s - %s NOT FOUND.\n", __FUNCTION__, semantic);
            
        return nullptr;
    }

    //----------------------------------------------------------------------
    //  inputのインデックスオフセット幅を取得
    int getIndexStride() const
    {
        int max_offset = 0;
        for (int i = 0; i < inputs_.size(); ++i) {
            int offset = inputs_[i].offset_;
            if (offset > max_offset) {
                max_offset = offset;
            }
        }

        return max_offset + 1;
    }

    //----------------------------------------------------------------------
    //  データ表示
    void dump()
    {
        
        for (int i = 0; i < sources_.size(); ++i) {
            sources_[i].dump();
        }

        for (int i = 0; i < inputs_.size(); ++i) {
            inputs_[i].dump();
        }

    }

    tinycollada::Indices raw_indices_;
    std::vector<char> face_count_;
    std::vector<SourceData> sources_;
    std::vector<InputData> inputs_;
    
};





//----------------------------------------------------------------------
//  ストライド幅を取得
uint32_t getStride(
    const tinyxml2::XMLElement* source_node
){
    const tinyxml2::XMLElement* technique_common = firstChildElement(
        source_node, 
        TECH_COMMON_NODE_NAME
    );
    const tinyxml2::XMLElement* accessor = firstChildElement(
        technique_common, 
        ACCESSOR_NODE_NAME
    );
    uint32_t stride;
    int check = accessor->QueryUnsignedAttribute(STRIDE_ATTR_NAME, &stride);
    if (check == tinyxml2::XML_NO_ATTRIBUTE) {
        stride = 1;
    }
        
    return stride;
}


//----------------------------------------------------------------------
//  配列データ読み込み
template <typename T>
void readArray(
    const char* text,
    std::vector<T>* container
){
    char* value_str = std::strtok(const_cast<char*>(text), " ");
    while (value_str) {
        T v = static_cast<T>(atof(value_str));
        container->push_back(v);
        value_str = std::strtok(nullptr, " ");
    }
}


//----------------------------------------------------------------------
//  ソース解析
void readSourceNode(
    const tinyxml2::XMLElement* const source_node,
    SourceData* out
) {
    const int ARRAY_TYPE_MAX = 2;
    char array_types[ARRAY_TYPE_MAX][15] = {
        "float_array",
        "int_array"
    };
        
    for (int i = 0; i < ARRAY_TYPE_MAX; ++i) {
        const tinyxml2::XMLElement* array_node = firstChildElement(
            source_node, 
            array_types[i]
        );
        if (!array_node) {
            continue;
        }
        //  データのストライドを取得
        out->stride_ = getStride(source_node);

        const char* text = array_node->GetText();
        //  データ数分のメモリをあらかじめリザーブ
        size_t data_count = 0;
        const char* count_str = getElementAttribute(array_node, COUNT_ATTR_NAME);
        if (count_str) {
            data_count = std::atoi(count_str);
        }
        TINY_COLLADA_TRACE("reserve %lu\n", data_count);
        out->data_.reserve(data_count);

        //  データ取得
        readArray(text, &out->data_);
    }
}


//----------------------------------------------------------------------
//  プリミティブノード取得
const tinyxml2::XMLElement* getPrimitiveNode(
    const tinyxml2::XMLElement* mesh_node
) {
    //  どのデータ構造でインデックスをもっているか調査
    for (int prim_idx = 0; prim_idx < PRIMITIVE_TYPE_NUM; ++prim_idx) {

        //  読み込めたら存在している
        const tinyxml2::XMLElement* primitive_node = firstChildElement(
            mesh_node,
            PRIMITIVE_TYPE_SELECT[prim_idx].name_
        );

        if (primitive_node) {
            return primitive_node;
        }
    }

    return nullptr;
}

//----------------------------------------------------------------------
//  プリミティブタイプ取得
tinycollada::ColladaMesh::PrimitiveType getPrimitiveType(
    const tinyxml2::XMLElement* mesh_node
) {
    //  どのデータ構造でインデックスをもっているか調査
    for (int prim_idx = 0; prim_idx < PRIMITIVE_TYPE_NUM; ++prim_idx) {

        //  読み込めたら存在している
        const tinyxml2::XMLElement* primitive_node = firstChildElement(
            mesh_node,
            PRIMITIVE_TYPE_SELECT[prim_idx].name_
        );

        if (primitive_node) {
            return PRIMITIVE_TYPE_SELECT[prim_idx].type_;
        }
    }

    return tinycollada::ColladaMesh::UNKNOWN_TYPE;
}


//----------------------------------------------------------------------
//  visual scene読み込み
void collectVisualSceneNode(
    VisualScenes& out,
    const tinyxml2::XMLElement* visual_scene_root
) {
    const tinyxml2::XMLElement* visual_scene = firstChildElement(visual_scene_root, "visual_scene");

    while (visual_scene) {
        const tinyxml2::XMLElement* visual_scene_node = firstChildElement(visual_scene, "node");
        while (visual_scene_node) {
            std::shared_ptr<VisualSceneData> vs = std::make_shared<VisualSceneData>();
            
            //  行列取得
            const tinyxml2::XMLElement* matrix_node = firstChildElement(visual_scene_node, "matrix");
            const char* mtx_text = matrix_node->GetText();
            readArray(mtx_text, &vs->matrix_);

            //  タイプ判定
            const tinyxml2::XMLElement* instance_geometry = firstChildElement(visual_scene_node, "instance_geometry");
            if (instance_geometry) {
                // ジオメトリノードだった
                vs->type_ = VisualSceneData::TYPE_GEOMETRY;
                const char* attr_url = getElementAttribute(instance_geometry, "url");
                if (attr_url[0] == '#') {
                    attr_url = &attr_url[1];
                }
                vs->url_ = attr_url;

            
                //  マテリアル取得
                const tinyxml2::XMLElement* bind_material = firstChildElement(
                    instance_geometry,
                    "bind_material"
                );
                if (bind_material) {
                    //  マテリアル設定があった
                    const tinyxml2::XMLElement* technique_common = firstChildElement(
                        bind_material,
                        "technique_common"
                    );
                    const tinyxml2::XMLElement* instance_material = firstChildElement(
                        technique_common,
                        "instance_material"
                    );
                    const char* attr_target = getElementAttribute(
                        instance_material,
                        "target"
                    );
                    if (attr_target[0] == '#') {
                        attr_target = &attr_target[1];
                    }
                    vs->bind_material_ = attr_target;
                }
            
            }
            
            out.push_back(vs);
            visual_scene_node = visual_scene_node->NextSiblingElement("node");
        }
        visual_scene = visual_scene->NextSiblingElement("visual_scene");
    }
}


//----------------------------------------------------------------------
//  マテリアルノード読み込み
void collectMaterialNode(
    Materials& out,
    const tinyxml2::XMLElement* library_materials
) {
    const tinyxml2::XMLElement* material = firstChildElement(library_materials, "material");

    while (material) {
        const tinyxml2::XMLElement* instance_effect = firstChildElement(material, "instance_effect");
        std::shared_ptr<MaterialData> md = std::make_shared<MaterialData>();
        md->id_ = getElementAttribute(material, "id");
        while (instance_effect) {
            const char* attr_url = getElementAttribute(instance_effect, "url");
            if (attr_url[0] == '#') {
                attr_url = &attr_url[1];
            }
            md->url_ = attr_url;
            instance_effect = instance_effect->NextSiblingElement("instance_effect");
        }
        
        out.push_back(md);
        material = material->NextSiblingElement("material");
    }
}


//----------------------------------------------------------------------
//  materialノード読み込み
void parseEffect(
    std::shared_ptr<tinycollada::ColladaMaterial>& material,
    const tinyxml2::XMLElement* shading
) {
    //  エミッション
    const tinyxml2::XMLElement* emission = firstChildElement(shading, "emission");
    if (emission) {
        const tinyxml2::XMLElement* color = firstChildElement(emission, "color");
        if (color) {
            const char* text = color->GetText();
            readArray(text, &material->emission_.color_);
        }
        
        //  エミッションマップテクスチャ
        const tinyxml2::XMLElement* texture = firstChildElement(emission, "texture");
        if (texture) {
            material->emission_.sampler_name_ = texture->Attribute("texture");
        }
    }
    //  アンビエント
    const tinyxml2::XMLElement* ambient = firstChildElement(shading, "ambient");
    if (ambient) {
        const tinyxml2::XMLElement* color = firstChildElement(ambient, "color");
        if (color) {
            const char* text = color->GetText();
            readArray(text, &material->ambient_.color_);
        }
        
        //  アンビエントマップテクスチャ
        const tinyxml2::XMLElement* texture = firstChildElement(ambient, "texture");
        if (texture) {
            material->ambient_.sampler_name_ = texture->Attribute("texture");
        }
    }

    //  ディフューズ
    const tinyxml2::XMLElement* diffuse = firstChildElement(shading, "diffuse");
    if (diffuse) {
        //  ディフューズカラー値
        const tinyxml2::XMLElement* color = firstChildElement(diffuse, "color");
        if (color) {
            const char* text = color->GetText();
            readArray(text, &material->diffuse_.color_);
        }
        //  ディフューズマップテクスチャ
        const tinyxml2::XMLElement* texture = firstChildElement(diffuse, "texture");
        if (texture) {
            material->diffuse_.sampler_name_ = texture->Attribute("texture");
        }

    }

    //  スペキュラ
    const tinyxml2::XMLElement* specular = firstChildElement(shading, "specular");
    if (specular) {
        const tinyxml2::XMLElement* color = firstChildElement(specular, "color");
        if (color) {
            const char* text = color->GetText();
            readArray(text, &material->specular_.color_);
        }

        //  スペキュラマップテクスチャ
        const tinyxml2::XMLElement* texture = firstChildElement(specular, "texture");
        if (texture) {
            material->specular_.sampler_name_ = texture->Attribute("texture");
        }
    }

    //  リフレクティブ
    const tinyxml2::XMLElement* reflective = firstChildElement(shading, "reflective");
    if (reflective) {
        const tinyxml2::XMLElement* color = firstChildElement(reflective, "color");
        if (color) {
            const char* text = color->GetText();
            readArray(text, &material->reflective_.color_);
        }
    }
    
    
    //  リフレクティビティ
    const tinyxml2::XMLElement* reflectivity = firstChildElement(shading, "reflectivity");
    if (reflectivity) {
        const tinyxml2::XMLElement* data = firstChildElement(reflectivity, "float");
        const char* val = data->GetText();

        material->reflectivity_ = std::atof(val);
    }

    //  シャイネス
    const tinyxml2::XMLElement* shininess = firstChildElement(shading, "shininess");
    if (shininess) {
        const tinyxml2::XMLElement* data = firstChildElement(shininess, "float");
        const char* val = data->GetText();

        material->shininess_ = atof(val);
    }
    
    //  透明度
    const tinyxml2::XMLElement* transparency = firstChildElement(shading, "transparency");
    if (transparency) {
        const tinyxml2::XMLElement* data = firstChildElement(transparency, "float");
        const char* val = data->GetText();

        material->transparency_ = atof(val);
    }

}


//----------------------------------------------------------------------
//  エフェクトノード読み込み
void collectEffectNode(
    Effects& out,
    const tinyxml2::XMLElement* library_effects
) {

    const tinyxml2::XMLElement* effect = firstChildElement(library_effects, "effect");

    while (effect) {

        std::shared_ptr<EffectData> ed = std::make_shared<EffectData>();
        ed->setupEffectData(effect);        
        out.push_back(ed);
        effect = effect->NextSiblingElement("effect");
    }

}


//----------------------------------------------------------------------
//  画像パス読み込み
void collectImageNode(
    Images& out,
    const tinyxml2::XMLElement* library_images
) {
    const tinyxml2::XMLElement* image = firstChildElement(library_images, "image");

    while (image) {
        //  ID取得
        std::shared_ptr<ImageData> image_data = std::make_shared<ImageData>();
        image_data->id_ = getElementAttribute(image, "id");


        //  テクスチャパス取得
        const tinyxml2::XMLElement* init_from = firstChildElement(image, "init_from");
        image_data->init_from_ = init_from->GetText();
        

        //  次へ
        out.push_back(image_data);
        image = image->NextSiblingElement("image");
    }

}


//----------------------------------------------------------------------
//  インデックス読み込み
void collectIndices(
    const tinyxml2::XMLElement* mesh_node,
    tinycollada::Indices& indices
) {        
    const tinyxml2::XMLElement* primitive_node = getPrimitiveNode(mesh_node);

    //  インデックス値読み込み
    if (primitive_node) {
        const tinyxml2::XMLElement* index_node = firstChildElement(primitive_node, INDEX_NODE_NAME);
        const char* text = index_node->GetText();
        readArray(text, &indices);
    }
    
    TINY_COLLADA_TRACE("Collect index size = %lu\n", indices.size());
}

//----------------------------------------------------------------------
//  面の頂点数読み込み
void collectFaceCount(
    const tinyxml2::XMLElement* mesh_node,
    std::vector<char>& face_count
) {        
    const tinyxml2::XMLElement* primitive_node = getPrimitiveNode(mesh_node);

    //  インデックス値読み込み
    if (primitive_node) {
        const tinyxml2::XMLElement* vcount_node = primitive_node->FirstChildElement("vcount");
        if (vcount_node) {
            char* text = const_cast<char*>(vcount_node->GetText());
            readArray(text, &face_count);
        }
    }
    
    TINY_COLLADA_TRACE("Collect face count size = %lu\n", face_count.size());
}



//----------------------------------------------------------------------
//  メッシュノードのソース情報を取得
void collectMeshSources(
    std::vector<SourceData>& out,
    const tinyxml2::XMLElement* mesh
){
    //  ソースノードを総なめして情報を保存
    const tinyxml2::XMLElement* target = firstChildElement(mesh, SOURCE_NODE_NAME);
    while (target) {
        SourceData data;
        //  ID保存
        data.id_ = getElementAttribute(target, ID_ATTR_NAME);
        
        //  配列データ保存
        readSourceNode(target, &data);

        //  コンテナに追加
        out.push_back(data);
        
        //  次へ
        target = target->NextSiblingElement(SOURCE_NODE_NAME);
    }
}

//----------------------------------------------------------------------
//  インプット情報を取得
void collectInputNodeData(
    std::vector<InputData>& out,
    const tinyxml2::XMLElement* input_node
) {
    while (input_node) {
        InputData input;
        //  sourceアトリビュートを取得
        const char* attr_source = getElementAttribute(input_node, SOURCE_NODE_NAME);
        //  source_nameの先頭の#を取る
        if (attr_source[0] == '#') {
            attr_source = &attr_source[1];
        }
        input.source_ = attr_source;
        input.semantic_ = getElementAttribute(input_node, SEMANTIC_ATTR_NAME);
        
        //  offsetアトリビュートを取得
        const char* attr_offset = getElementAttribute(input_node, OFFSET_ATTR_NAME);
        int offset = 0;
        if (attr_offset) {
            offset = atoi(attr_offset);
        }
        input.offset_ = offset;


        //  インプットノード保存
        out.push_back(input);

        //  次へ
        input_node = input_node->NextSiblingElement(INPUT_NODE_NAME);
    }
 
}

//----------------------------------------------------------------------
//  インプット情報を取得
void collectMeshInputs(
    std::vector<InputData>& out,
    const tinyxml2::XMLElement* mesh
){
    //  primitiveノード
    const tinyxml2::XMLElement* primitive_node = getPrimitiveNode(mesh);
	if (!primitive_node) {
		return;
	}
    const tinyxml2::XMLElement* prim_input_node = firstChildElement(primitive_node, INPUT_NODE_NAME);
    collectInputNodeData(out, prim_input_node);
    
    //  vertices_node
    const tinyxml2::XMLElement* vertices =  firstChildElement(mesh, VERTICES_NODE_NAME);
    const tinyxml2::XMLElement* vert_input_node = firstChildElement(vertices, INPUT_NODE_NAME);
    collectInputNodeData(out, vert_input_node);
}

std::shared_ptr<tinycollada::ColladaMaterial> searchMaterial(
    const char* bind_material,
    const Materials& materials,
    const Effects& effects
) {
    //  マテリアルを探す
    const char* effect_url = nullptr;
    for (int i = 0; i < materials.size(); ++i) {
        if (std::strncmp(materials[i]->id_, bind_material, PARSE_STRING_SIZE) == 0) {
            //  あった
            effect_url = materials[i]->url_;
            break;
        }
    }

    if (!effect_url) {
        //  指定マテリアルは存在しなかった
        return nullptr;
    }

    //  エフェクトを探す
    std::shared_ptr<tinycollada::ColladaMaterial> mat = nullptr;
    for (int i = 0; i < effects.size(); ++i) {
        if (std::strncmp(effect_url, effects[i]->id_, PARSE_STRING_SIZE) == 0) {
            //  あった
            mat = effects[i]->material_;
        }
    }


    
    return mat;
}



void transposeMatrix(std::vector<float>& mtx)
{
    for (int x = 0; x < 4; ++x) {
        for (int y = x; y < 4;++y) {
            if (x == y) {
                continue;
            }
            int xy = x * 4 + y;
            int yx = y * 4 + x;
            std::swap(mtx[xy], mtx[yx]);
        }
    }

}

}   // unname namespace


namespace tinycollada {



class Parser::Impl
{
public:
    Impl()
        : scenes_()
    {}

    ~Impl()
    {}

    
    //----------------------------------------------------------------------
    Result parseCollada(
        const tinyxml2::XMLDocument* const doc
    ) {
        
        //  ルートノード取得
        const tinyxml2::XMLElement* root_node = doc->RootElement();


        //  visual_scene解析
        const tinyxml2::XMLElement* library_visual_scene = firstChildElement(
            root_node,
            "library_visual_scenes"
        );
        collectVisualSceneNode(visual_scenes_, library_visual_scene);

        //  マテリアルノード解析
        const tinyxml2::XMLElement* library_materials = firstChildElement(root_node, "library_materials");
        if (library_materials) {
            collectMaterialNode(materials_, library_materials);
        }
        
        //  エフェクトノード解析
        const tinyxml2::XMLElement* library_effects = firstChildElement(root_node, "library_effects");
        if (library_effects) {
            collectEffectNode(effects_, library_effects);
        }

        //  テクスチャパス解析
        const tinyxml2::XMLElement* library_images = firstChildElement(root_node, "library_images");
        if (library_images) {
            collectImageNode(images_, library_images);
        }


        //  ダンプ
        for (int i = 0; i < visual_scenes_.size(); ++i) {
            visual_scenes_[i]->dump();
        }
        for (int i = 0; i < materials_.size(); ++i) {
            materials_[i]->dump();
        }
        for (int i = 0; i < effects_.size(); ++i) {
            effects_[i]->dump();
        }
        for (int i = 0; i < images_.size(); ++i) {
            images_[i]->dump();
        }

        //  ジオメトリノード解析
        const tinyxml2::XMLElement* library_geometries = firstChildElement(
            root_node,
            LIB_GEOMETRY_NODE_NAME
        );
        
        
        for (int vs_idx = 0; vs_idx < visual_scenes_.size(); ++vs_idx) {
            std::shared_ptr<VisualSceneData>& vs = visual_scenes_[vs_idx];
            if (vs->type_ != VisualSceneData::TYPE_GEOMETRY) {
                continue;
            }

            //  シーン作成
            //  構築したデータの受け皿
            std::shared_ptr<ColladaScene> scene = std::make_shared<ColladaScene>();

            // ------------------
            //  マトリックス登録
            transposeMatrix(vs->matrix_);
            scene->matrix(vs->matrix_);
            scenes_.push_back(scene);

            // ------------------
            //  マテリアル設定
            auto a=searchMaterial(vs->bind_material_, materials_, effects_);
            scene->material(a);
        
            // ------------------
            //  メッシュ情報生成
            
            //  geometryを走査して、現在のシーンのメッシュデータを持っている場所を探す
            const tinyxml2::XMLElement* geometry = firstChildElement(
                library_geometries,
                GEOMETRY_NODE_NAME
            );

            while (geometry) {
                //  新しいジオメトリのID取得
                const char* geometry_id = getElementAttribute(geometry, "id");

                //  目的の名前か判定
                if (std::strncmp(vs->url_, geometry_id, PARSE_STRING_SIZE) != 0) {
                    //  違うので再チャレンジ
                    geometry = geometry->NextSiblingElement(GEOMETRY_NODE_NAME);
                } else {
                    //  見つけた
                    break;
                }
            }
            
            if (!geometry) {
                //  対象のデータを持ったジオメトリは無い！
                continue;
            }
            
            //
            //  以下、ジオメトリを見つけたのでメッシュ構造を解析する
            //
            
            //  メッシュデータ解析
            const tinyxml2::XMLElement* mesh_node = firstChildElement(
                geometry,
                MESH_NODE_NAME
            );
            while (mesh_node) {
            
                std::shared_ptr<ColladaMesh> mesh = std::make_shared<ColladaMesh>();
                parseMeshNode(mesh_node, mesh);
                
                //  データ登録
                scene->addMesh(mesh);
                
                //  次へ
                mesh_node = mesh_node->NextSiblingElement(MESH_NODE_NAME);
            }
        }
        
        return Result::Code::SUCCESS;
    }

    //----------------------------------------------------------------------
    //  メッシュノードの解析
    void parseMeshNode(
        const tinyxml2::XMLElement* mesh_node,
        ::std::shared_ptr<tinycollada::ColladaMesh> mesh
    ) {
        std::shared_ptr<MeshInformation> info = std::make_shared<MeshInformation>();

        //  インデックス情報保存
        collectIndices(mesh_node, info->raw_indices_);
        collectFaceCount(mesh_node, info->face_count_);

        //  ソースノードの情報保存
        collectMeshSources(info->sources_, mesh_node);
        
        //  インプットノードの情報保存
        collectMeshInputs(info->inputs_, mesh_node);
        
        info->dump();
        
        //  ソースとインプットを関連付け
        relateSourcesToInputs(info);
        printf("\n\n");
        for (int i = 0; i < info->sources_.size(); ++i) {
            SourceData* src = &info->sources_[i];
            if (src->input_) {
                printf("SRC:%s - INPUT:%s\n", src->id_, src->input_->source_);
                printf("  DATA size %lu\n", src->data_.size());
            }
        }
        printf("\n\n");


        setupMesh(mesh_node, info, mesh);
        
    }

    //----------------------------------------------------------------------
    void setupMesh(
        const tinyxml2::XMLElement* mesh_node,
        std::shared_ptr<MeshInformation> info,
        std::shared_ptr<tinycollada::ColladaMesh> mesh
    ) {
        //  プリミティブの描画タイプを設定
        tinycollada::ColladaMesh::PrimitiveType prim_type = getPrimitiveType(mesh_node);
        mesh->setPrimitiveType(prim_type);

        int offset_size = info->getIndexStride();

        //  頂点情報
        const SourceData* pos_source = info->searchSourceBySemantic("POSITION");
        if (pos_source) {

            //  ソース情報をコピー
            printf("pos_source size %lu\n", pos_source->data_.size());
            mesh->vertices().data(pos_source->data_);
            mesh->vertices().stride(pos_source->stride_);

            if (info->face_count_.empty()) {
                //  面情報がカラ
                setupIndices(
                    mesh->vertices().indices(),
                    info->raw_indices_,
                    pos_source->input_->offset_,
                    offset_size
                );
            }
            else {
                setupIndicesMultiFace(
                    mesh->vertices().indices(),
                    info,
                    pos_source->input_->offset_,
                    offset_size
                );
            }
        }

        //  法線情報
        const SourceData* normal_source = info->searchSourceBySemantic("NORMAL");
        if (normal_source) {
            printf("normal_source size %lu\n", normal_source->data_.size());
            
            mesh->normals().stride(normal_source->stride_);
            if (info->face_count_.empty()) {
                setupIndices(
                    mesh->normals().indices(),
                    info->raw_indices_,
                    normal_source->input_->offset_,
                    offset_size
                );
            }
            else {
                setupIndicesMultiFace(
                    mesh->normals().indices(),
                    info,
                    normal_source->input_->offset_,
                    offset_size
                );
            }
            
            mesh->normals().data(normal_source->data_);
            //  頂点インデックスにあわせてデータ変更
/*
            Indices& vindices = mesh->vertices().indices();
            Indices& nindices = mesh->normals().indices();
            mesh->normals().data().resize(pos_source->data_.size(), 8.8);
            auto& normal_data = mesh->normals().data();
            for (int vert_idx = 0; vert_idx < vindices.size(); ++vert_idx) {
                uint32_t vidx = vindices.at(vert_idx);
                uint32_t nidx = nindices.at(vert_idx);
                uint32_t nstride = normal_source->stride_;
                uint32_t from_idx = nidx * nstride;
                uint32_t to_idx = vidx * nstride;
                printf("%d-%d\n", vidx, nidx);
                for (int di = 0; di < nstride; ++di) {
                    int to = to_idx + di;
                    int from = from_idx + di;
                    printf("　　%d -> %d\n", from, to );
                    normal_data[to_idx + di] = normal_source->data_.at(from_idx + di);
                }
            }
*/
            
            
        }


        //  uv
        const SourceData* uv_source = info->searchSourceBySemantic("TEXCOORD");
        if (uv_source) {
            printf("uv_source size %lu\n", uv_source->data_.size());
            
            mesh->uvs().stride(uv_source->stride_);
            if (info->face_count_.empty()) {
                setupIndices(
                    mesh->uvs().indices(),
                    info->raw_indices_,
                    uv_source->input_->offset_,
                    offset_size
                );
            }
            else {
                setupIndicesMultiFace(
                    mesh->uvs().indices(),
                    info,
                    uv_source->input_->offset_,
                    offset_size
                );
            }

            mesh->uvs().data(uv_source->data_);
            
        }
    }




    //----------------------------------------------------------------------
    //  事前に抜いておいたインデックス一覧からインデックスのセットアップ
    void setupIndices(
        Indices& out,
        Indices& src,
        int start_offset,
        int stride
    ) {
        TINY_COLLADA_TRACE("%s start_offset = %d stride = %d\n", __FUNCTION__, start_offset, stride);
        for (int i = start_offset; i < src.size(); i += stride) {
            out.push_back(src.at(i));
        }
        TINY_COLLADA_TRACE("index size = %lu\n", out.size());
    }

    //----------------------------------------------------------------------
    //  事前に抜いておいたインデックス一覧からインデックスのセットアップ2
    void setupIndicesMultiFace(
        Indices& out,
        std::shared_ptr<MeshInformation>& info,
        int start_offset,
        int stride
    ) {
        int idx = start_offset;
        for (int i = 0; i < info->face_count_.size(); ++ i) {
            int vcnt = info->face_count_.at(i);

            if (vcnt == 3) {
                uint32_t idx1 = info->raw_indices_.at(idx);
                idx += stride;
                uint32_t idx2 = info->raw_indices_.at(idx);
                idx += stride;
                uint32_t idx3 = info->raw_indices_.at(idx);
                idx += stride;
                out.push_back(idx1);
                out.push_back(idx2);
                out.push_back(idx3);

            }
            else if (vcnt == 4) {
                uint32_t idx1 = info->raw_indices_.at(idx);
                idx += stride;
                uint32_t idx2 = info->raw_indices_.at(idx);
                idx += stride;
                uint32_t idx3 = info->raw_indices_.at(idx);
                idx += stride;
                uint32_t idx4 = info->raw_indices_.at(idx);
                idx += stride;

                out.push_back(idx1);
                out.push_back(idx2);
                out.push_back(idx3);

                out.push_back(idx1);
                out.push_back(idx3);
                out.push_back(idx4);
            }
        }
    }

        
    //----------------------------------------------------------------------
    //  メッシュから抜いたinputsとsourcesを関連付ける
    void relateSourcesToInputs(
        std::shared_ptr<MeshInformation>& info
    )
    {
        TINY_COLLADA_TRACE("%s\n", __FUNCTION__);
        auto src_it = info->sources_.begin();
        auto src_end = info->sources_.end();
        

        while (src_it != src_end) {
            InputData* input = info->searchInputBySource(src_it->id_);
            src_it->input_ = input;
            
            TINY_COLLADA_TRACE(" %s", src_it->id_);
            if (input) {
                TINY_COLLADA_TRACE(" OK\n");
                TINY_COLLADA_TRACE("  %s %s\n", input->semantic_, input->source_);
            }
            else {
                TINY_COLLADA_TRACE(" NG\n");
            }
            ++src_it;
        }
    }
        


    //----------------------------------------------------------------------
    //  メッシュリスト取得
    const ColladaScenes* getScenes() const {
        return &scenes_;
    }


public:
    //  init_fromでテクスチャ名を検索
    const char* getTextureNameFromInitFrom(
        const char* const init_from
    ) {
        for (int i = 0; i < images_.size(); ++i) {
            auto& image = images_.at(i);
            
            if (std::strncmp(init_from, image->id_, PARSE_STRING_SIZE) == 0) {
                return image->init_from_;
            }
        }
    
        return nullptr;
    }
    
    const char* getInitFromFromSurface(
        const char* const surface_name
    ) {
        for (int i = 0; i < effects_.size(); ++i) {
            auto& effect = effects_.at(i);
            auto& surface = effect->surface_;
            const char* eff_sid = surface->sid_;
            if (std::strncmp(eff_sid, surface_name, PARSE_STRING_SIZE) == 0) {
                return surface->init_from_;
            }
        }
        return nullptr;
    }
    
    const char* getSurfaceFromSampler(
        const char* const sampler_name
    ) {
    
        for (int i = 0; i < effects_.size(); ++i) {
            auto& effect = effects_.at(i);
            auto& sampler = effect->sampler2d_;
            
            const char* eff_sampler = sampler->sid_;
            if (std::strncmp(eff_sampler, sampler_name, PARSE_STRING_SIZE) == 0) {
                return sampler->source_;
            }
        }
    
        return nullptr;
    }
    
    const char* getTextureNameFromSampler(
        const char* const sampler_name
    ) {
        const char* surface_name = getSurfaceFromSampler(sampler_name);
        if (surface_name) {
            const char* init_from = getInitFromFromSurface(surface_name);
            if (init_from) {
                return getTextureNameFromInitFrom(init_from);
            }
        }
        
    
        return nullptr;
    }


private:
    ColladaScenes scenes_;
    
    VisualScenes visual_scenes_;
    Materials materials_;
    Images images_;
    Effects effects_;
    
};  // class Parser::Impl



//----------------------------------------------------------------------
Parser::Parser()
    : impl_(nullptr)
{
    impl_.reset(new Impl());
}

//----------------------------------------------------------------------
Parser::~Parser()
{
}

//----------------------------------------------------------------------
Result Parser::parse(
    const char* const dae_path
) {
   
    //  tiny xmlを使って.daeを読み込む
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError load_error = doc.LoadFile(dae_path);
    if (load_error != tinyxml2::XML_SUCCESS) {
        return Result::Code::READ_ERROR;
    }
//    doc.Print();


    //  解析
    Result parse_result = impl_->parseCollada(&doc);
    if (parse_result.isFailed()) {
        return parse_result;
    }

    return Result::Code::SUCCESS;
}


const ColladaScenes* Parser::scenes() const {
    return impl_->getScenes();
}

const char* Parser::getTextureNameFromSampler(
    const char* const sampler
) {
    return impl_->getTextureNameFromSampler(sampler);
}

//----------------------------------------------------------------------
//  データをコンソールに出力
void ColladaMesh::dump() {
    printf("--- Vertex data dump ---\n");
    vertices().dump();
    printf("\n");
    printf("--- Normal data dump ---\n");
    normal_.dump();
    printf("\n");
    
}

//----------------------------------------------------------------------
//  データをコンソールに出力
void ColladaMesh::ArrayData::dump() {
    if (!isValidate()) {
        printf("This ArrayData is invalidate data.\n");
        return;
    }
    printf("vertices   size = %lu  stride = %hhd\n", data_.size(), stride());
    size_t data_size = data_.size();
    //  データ
    if (data_size > 0) {
        for (size_t i = 0; i < data_size; ++i) {
            printf(" %f", data_[i]);
        }
        printf("\n");
    }
    else {
        printf("nothing.\n");
    }
    
    //  インデックス
    printf("indices   size = %lu\n", indices().size());
    size_t idx_size = indices().size();
    //  データ
    if (idx_size > 0) {
        for (size_t i = 0; i < idx_size; ++i) {
            printf(" %d", indices()[i]);
        }
        printf("\n");
    }
    else {
        printf("nothing.\n");
    }
    
    
}

}   // namespace tc

