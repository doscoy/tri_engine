////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/loader/tri_dae_loader.hpp"
#include "core/graphics/tri_vertex_types.hpp"
#include "../../../third_party/tiny_collada/tiny_collada_parser.hpp"



TRI_CORE_NS_BEGIN



SubMeshesDataPtr DaeLoader::load(
    const char* const path
) {
    //  戻すサブメッシュ
    auto submeshes = std::make_shared<SubMeshesData>();

    //  daeをパース
    tinycollada::Parser parser;
    parser.parse(path);
    const auto& scenes = parser.scenes();

    for (int i = 0; i < scenes->size(); ++i) {

        auto submesh = std::make_shared<SubMeshData>();

        const auto& s = scenes->at(i);
        //  シーンからメッシュを取り出す
        auto& meshes = s->meshes();

        auto& bm = s->matrix();
        Mtx44 mtx(
            bm[ 0], bm[ 1], bm[ 2], bm[ 3],
            bm[ 4], bm[ 5], bm[ 6], bm[ 7],
            bm[ 8], bm[ 9], bm[10], bm[11],
            bm[12], bm[13], bm[14], bm[15]
        );
        submesh->matrix(mtx);
        
        
        //  マテリアル取得
        auto& scene_material = s->material();
        auto new_material = Material::create();
        if (scene_material.get()) {
            // -----------------------
            //  ディフューズ
            auto& diffuse = scene_material->diffuse_;
            //  RGBカラー値の取得
            if (diffuse.color_.empty()) {
                //  ディフューズが空
            } else {
                //  ディフューズ値があった
                new_material->diffuse(Color(
                    static_cast<uint_fast8_t>(diffuse.color_.at(0) * 255.0f),
                    static_cast<uint_fast8_t>(diffuse.color_.at(1) * 255.0f),
                    static_cast<uint_fast8_t>(diffuse.color_.at(2) * 255.0f),
                    static_cast<uint_fast8_t>(diffuse.color_.at(3) * 255.0f)
                ));
            }
            
            //  ディフューズマップが指定されているか
            if (diffuse.sampler_name_) {
                //  ディフューズマップあり
                String diffuse_map_name = parser.getTextureNameFromSampler(diffuse.sampler_name_);
                if (diffuse_map_name.find("file:///", 0) != String::npos) {
                    // 余分な文字列付き file:///
                    diffuse_map_name.erase(0, 8);
                }

                FilePath tex_path = diffuse_map_name;
                auto t = Texture::create(tex_path);
                new_material->diffuseMap(t);
            }

            // -----------------------
            //  アンビエント
            auto& ambient = scene_material->ambient_;
            if (ambient.color_.empty()) {
                //  アンビエントが空
            } else {
                //  アンビエント値があった
                new_material->ambient(Color(
                    static_cast<int_fast8_t>(ambient.color_.at(0) * 255.0f),
                    static_cast<int_fast8_t>(ambient.color_.at(1) * 255.0f),
                    static_cast<int_fast8_t>(ambient.color_.at(2) * 255.0f),
                    static_cast<int_fast8_t>(ambient.color_.at(3) * 255.0f)
                ));
            
            }


            // -----------------------
            //  スペキュラ
            new_material->specular(Color(
                static_cast<uint_fast8_t>(scene_material->specular_.color_.at(0) * 255.0f),
                static_cast<uint_fast8_t>(scene_material->specular_.color_.at(1) * 255.0f),
                static_cast<uint_fast8_t>(scene_material->specular_.color_.at(2) * 255.0f),
                static_cast<uint_fast8_t>(scene_material->specular_.color_.at(3) * 255.0f)
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
            auto index_size = mesh->vertices().indices().size();
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
                auto uv_index_size = mesh_uvs_indices.size();
                for (int uv_idx_loop = 0; uv_idx_loop < uv_index_size; ++uv_idx_loop) {
                    uv_indices.push_back(mesh_uvs_indices.at(uv_idx_loop));
                }

            }


        }


        //  最終的にワンインデックスのストリームを作る
        auto indices_size = indices.size();
        for (int indices_idx = 0; indices_idx < indices_size; ++indices_idx) {
            SubMeshData::VerticesType::value_type vtx;
            if (has_uv) {
                //  取得したUVのインデックス値が、集めたUVの数以内に収まってるかチェック
                int target_uv_index = uv_indices.at(indices_idx);
                T3_ASSERT(target_uv_index < uvs.size());

                //  インデックスで並び替える
                vtx.uv_ = uvs.at(target_uv_index);
            
            } else {
                vtx.uv_ = Vec2(0,0);
            }
            vtx.normal_ = vertices.at(indices.at(indices_idx)).normal_;
            vtx.position_ = vertices.at(indices.at(indices_idx)).position_;
            
            submesh->vertices().push_back(vtx);
            submesh->indices().push_back(indices_idx);
        }


        //  出来上がったサブメッシュの法線を計算
        for (int face_idx = 0; face_idx < submesh->indices().size(); face_idx += 3) {
            int i0 = submesh->indices().at(face_idx);
            int i1 = submesh->indices().at(face_idx + 1);
            int i2 = submesh->indices().at(face_idx + 2);
            
            auto& v0 = submesh->vertices().at(i0);
            auto& v1 = submesh->vertices().at(i1);
            auto& v2 = submesh->vertices().at(i2);
            
            
            Vec3 vec0 = v0.position_ - v1.position_;
            Vec3 vec1 = v0.position_ - v2.position_;
            auto n = vec0.crossProduct(vec1);
            n.normalize();
            v0.normal_ += n;
            v1.normal_ += n;
            v2.normal_ += n;
        }

        //  メッシュ追加
        submeshes->push_back(submesh);
    }

  


    return submeshes;
}

TRI_CORE_NS_END

