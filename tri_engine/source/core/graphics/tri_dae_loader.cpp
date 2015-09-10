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
    for (int i = 0; i < scenes->size(); ++i) {
        const auto& s = scenes->at(i);
        //  シーンからメッシュを取り出す
        auto& meshes = s->meshes_;
        for (int mesh_idx = 0; mesh_idx < meshes.size(); ++mesh_idx) {
            //  メッシュを走査
            const auto& mesh = meshes.at(mesh_idx);
            if (!mesh->hasVertex()) {
                //  頂点情報を持ってないメッシュはスキップ
                continue;
            }

            //  頂点をコピー
            submesh->vertices() = mesh->vertices().data()
        }
    }

  

    

    return submesh;
}

TRI_CORE_NS_END

