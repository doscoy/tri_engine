
#include "gfx/tri_model.hpp"
#include "gfx/tri_vertex_types.hpp"
#include "kernel/memory/tri_new.hpp"
#include "../shader/tri_simple3d.vsh"
#include "../shader/tri_simple3d.fsh"

namespace  {


const char* SHADER_ATTR_POSITION = "a_position";
const char* SHADER_ATTR_NORMAL = "a_normal";
const char* SHADER_ATTR_UV = "a_uv";
const char* SHADER_UNIF_PMV = "u_pmv";

}


namespace t3 {



Model::Model()
    : mesh_(nullptr)
    , default_shader_()
    , current_shader_(&default_shader_) {

    //  シェーダ作成
    default_shader_.build(simple3d_vsh, simple3d_fsh);

}


Model::~Model() {


}



void Model::render(const Mtx44& transform) {

    cross::RenderSystem::resetBufferBind();

    current_shader_->use();
    current_shader_->setUniform(SHADER_UNIF_PMV, transform);
//頂点配列を有効化
    current_shader_->setUniform("sampler", 0);
    

    cross::RenderSystem::setActiveTextureUnit(
        cross::RenderSystem::TextureUnit::UNIT0
    );

    mesh_->vertexBuffer().bind();
    mesh_->indexBuffer().bind();

    auto& material = mesh_->material();

    material->texture()->bind();

    //  頂点座標有効化
    current_shader_->setEnableAttributeArray(SHADER_ATTR_POSITION, true);
    current_shader_->setAttributePointer(
        SHADER_ATTR_POSITION,
        3,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VertexP3NT),
        0
    );

    //  頂点法線有効化
    if (current_shader_->setEnableAttributeArray(SHADER_ATTR_NORMAL, true)) {
        current_shader_->setAttributePointer(
            SHADER_ATTR_NORMAL,
            3,
            cross::RenderSystem::TypeFormat::FLOAT,
            false,
            sizeof(VertexP3NT),
            (void*)offsetof(VertexP3NT, normal_)
        );
    }

    //  UV有効化
    current_shader_->setEnableAttributeArray(SHADER_ATTR_UV, true);
    current_shader_->setAttributePointer(
        SHADER_ATTR_UV,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VertexP3NT),
        (void*)offsetof(VertexP3NT, uv_)
    );



    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);
    cross::RenderSystem::setDepthTest(true);


    cross::RenderSystem::drawElements(
        cross::RenderSystem::DrawMode::MODE_TRIANGLES,
        mesh_->indexCount(),
        sizeof(uint32_t)
    );
    
}


//  モデル生成関数
ModelPtr Model::create() {
    ModelPtr m(T3_NEW Model);
    return m;
}

ModelPtr Model::create(
    const char* const mesh_path
) {
    Mesh* mesh = T3_NEW Mesh(mesh_path);
    ModelPtr m(T3_NEW Model);
    m->mesh(mesh);
    return m;
}



}   // namespace t3

