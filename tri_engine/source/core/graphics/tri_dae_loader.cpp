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
    auto& meshes = s->meshes();


    //  マテリアル取得
    auto& scene_material = s->material();
    auto new_material = Material::create();
    if (scene_material.get()) {
        new_material->diffuse(Color(
            scene_material->diffuse_.at(0),
            scene_material->diffuse_.at(1),
            scene_material->diffuse_.at(2),
            scene_material->diffuse_.at(3)
        ));

        new_material->ambient(Color(
            scene_material->ambient_.at(0),
            scene_material->ambient_.at(1),
            scene_material->ambient_.at(2),
            scene_material->ambient_.at(3)
        ));

        new_material->specular(Color(
            scene_material->specular_.at(0),
            scene_material->specular_.at(1),
            scene_material->specular_.at(2),
            scene_material->specular_.at(3)
        ));
    }


    //  マテリアル設定
    submesh->material(new_material);

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

    bool has_uv = false;

    for (int mesh_idx = 0; mesh_idx < meshes.size(); ++mesh_idx) {
        //  メッシュを走査
        const auto& mesh = meshes.at(mesh_idx);
        if (!mesh->hasVertex()) {
            //  頂点情報を持ってないメッシュはスキップ
            continue;
        }



        auto& mesh_vertex = mesh->vertices();
        auto& mesh_vertex_data = mesh_vertex.data();

        // ------------------------------------------
        //  頂点をコピー
        int stride = mesh->vertices().stride();
        T3_ASSERT(stride == 3);

       
        for (int vindex = 0; vindex < mesh_vertex_data.size(); vindex += stride) {
            
            //  座標設定
            SubMeshData::VerticesType::value_type p3nt;
            p3nt.position_.x_ = mesh_vertex_data[vindex];
            p3nt.position_.y_ = mesh_vertex_data[vindex + 1];
            p3nt.position_.z_ = mesh_vertex_data[vindex + 2];

            vertices.push_back(p3nt);
        }

            
        //  頂点インデックス
        int index_size = mesh->vertices().indices().size();
        for (int index_loop = 0; index_loop < index_size; ++index_loop) {
            indices.push_back(mesh->vertices().indices().at(index_loop));
        }

        // ------------------------------------------
        //  UVを取得
        auto& mesh_uvs = mesh->uvs();
        auto& mesh_uvs_data = mesh_uvs.data();
        if (mesh->hasTexCoord()) {
            has_uv = true;
            //  UVがある
            for (int uvindex = 0; uvindex < mesh_uvs_data.size(); uvindex += 2) {
                Vec2 uv = Vec2(
                    mesh_uvs_data.at(uvindex), 
                    mesh_uvs_data.at(uvindex + 1)
                );
                uvs.push_back(uv);
            }


            //  UVインデックス
            auto& mesh_uvs_indices = mesh_uvs.indices();
            int uv_index_size = mesh_uvs_indices.size();
            for (int uv_idx_loop = 0; uv_idx_loop < uv_index_size; ++uv_idx_loop) {
                uv_indices.push_back(mesh_uvs_indices.at(uv_idx_loop));
            }

        }


    }
//    }

  
        //  最終的にワンインデックスのストリームを作る


    int indices_size = indices.size();
    for (int i = 0; i < indices_size; ++i) {
        SubMeshData::VerticesType::value_type vtx;
        if (has_uv) {
            //  取得したUVのインデックス値が、集めたUVの数以内に収まってるかチェック
            int target_uv_index = uv_indices.at(i);
            T3_ASSERT(target_uv_index < uvs.size());

            //  インデックスで並び替える
            vtx.uv_ = uvs.at(target_uv_index);
        
        } else {
            vtx.uv_ = Vec2(0,0);
        }
        vtx.normal_ = vertices.at(indices.at(i)).normal_;
        vtx.position_ = vertices.at(indices.at(i)).position_;
        
        submesh->vertices().push_back(vtx);
        submesh->indices().push_back(i);
    }


    return submesh;
}

TRI_CORE_NS_END

