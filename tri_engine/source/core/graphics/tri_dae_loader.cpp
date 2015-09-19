#include "core/graphics/tri_dae_loader.hpp"
#include "core/graphics/tri_vertex_types.hpp"
#include "../../third_party/tiny_collada/tiny_collada_parser.hpp"



TRI_CORE_NS_BEGIN



SubMeshDataPtr DaeLoader::load(
    const char* const path
) {
    //  戻すサブメッシュ
    SubMeshDataPtr submesh = std::make_shared<SubMeshData>();

    //  daeをパース
    tinycollada::Parser parser;
    parser.parse(path);



    const auto& scenes = parser.scenes();
//    for (int i = 0; i < scenes->size(); ++i) {

    const auto& s = scenes->at(0);
    //  シーンからメッシュを取り出す
    auto& meshes = s->meshes_;


    //  頂点
    SubMeshData::VerticesType vertices;
    vertices.reserve(1000);

    //  頂点インデックス
    SubMeshData::IndicesType indices;
    indices.reserve(1000);
    
    //  UV
    Vector<Vec2> uvs;
    uvs.reserve(1000);
    
    //  UVインデックス
    SubMeshData::IndicesType uv_indices;
    uv_indices.reserve(1000);

    for (int mesh_idx = 0; mesh_idx < meshes.size(); ++mesh_idx) {
        //  メッシュを走査
        const auto& mesh = meshes.at(mesh_idx);
        if (!mesh->hasVertex()) {
            //  頂点情報を持ってないメッシュはスキップ
            continue;
        }

        auto& mesh_vertex = mesh->vertices();
        auto& mesh_vertex_data = mesh_vertex.data();

        //  頂点をコピー
        int strid = mesh->vertices().stride();
        T3_ASSERT(strid == 3);

        int vertex_num = mesh_vertex_data.size() / stride;
       
        for (int vindex = 0; vindex < mesh_vertex_data.size(); vindex += stride) {
            
            //  座標設定
            SubMeshData::VerticesType::value_type p3nt;
            p3nt.position_.x_ = mesh_vertex_data[vindex];
            p3nt.position_.y_ = mesh_vertex_data[vindex + 1];
            p3nt.position_.z_ = mesh_vertex_data[vindex + 2];

            vertices.push_back(p3nt);
        }

        //  UVを取得
        auto& mesh_uvs = mesh->uvs();
        auto& mesh_uvs_data = mesh_usv
        if (mesh->hasTexCoord()) {
            //  UVがある
            for (int uvindex = 0; uvindex < )
        }

            
        //  インデックス
        int index_size = mesh->vertices().indices().size();
        for (int index_loop = 0; index_loop < index_size; ++index_loop) {
            indices.push_back(mesh->vertices().indices().at(index_loop));
        }
    }
//    }

  
    
        //  最終的にワンインデックスのストリームを作る


    int indices_size = indices.size();
    for (int i = 0; i < indices_size; ++i) {
        SubMeshData::VerticesType::value_type vtx;
        
        T3_ASSERT(uv_indices.at(i) < uvs.size());
        vtx.uv_ = uvs.at(uv_indices.at(i));
        vtx.normal_ = vertices.at(indices.at(i)).normal_;
        vtx.position_ = vertices.at(indices.at(i)).position_;
        
        submesh->vertices().push_back(vtx);
        submesh->indices().push_back(i);
    }


    return submesh;
}

TRI_CORE_NS_END

