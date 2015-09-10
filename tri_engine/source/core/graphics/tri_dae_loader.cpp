#include "core/graphics/tri_dae_loader.hpp"
#include "core/graphics/tri_vertex_types.hpp"
#include "../../third_party/tiny_collada/tiny_collada_parser.hpp"



TRI_CORE_NS_BEGIN



SubMeshDataPtr DaeLoader::load(
    const char* const path
) {
    //  �߂��T�u���b�V��
    SubMeshDataPtr submesh = std::make_shared<SubMeshData>();

    //  dae���p�[�X
    tinycollada::Parser parser;
    parser.parse(path);

    const auto& scenes = parser.scenes();
    for (int i = 0; i < scenes->size(); ++i) {
        const auto& s = scenes->at(i);
        //  �V�[�����烁�b�V�������o��
        auto& meshes = s->meshes_;
        for (int mesh_idx = 0; mesh_idx < meshes.size(); ++mesh_idx) {
            //  ���b�V���𑖍�
            const auto& mesh = meshes.at(mesh_idx);
            if (!mesh->hasVertex()) {
                //  ���_���������ĂȂ����b�V���̓X�L�b�v
                continue;
            }

            //  ���_���R�s�[
            submesh->vertices() = mesh->vertices().data()
        }
    }

  

    

    return submesh;
}

TRI_CORE_NS_END

