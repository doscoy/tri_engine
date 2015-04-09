
#include "gfx/tri_model.hpp"
#include "gfx/tri_vertex_types.hpp"

#include "../shader/tri_simple.vsh"
#include "../shader/tri_simple.fsh"

namespace  {


const char* SHADER_ATTR_POSITION = "a_position";
const char* SHADER_ATTR_NORMAL = "a_normal";

const char* SHADER_UNIF_PMV = "u_pmv";

}


namespace t3 {
inline namespace gfx {


Model::Model()
    : mesh_(nullptr)
    , default_shader_()
    , current_shader_(&default_shader_) {

    //  シェーダ作成
    default_shader_.build(SimpleVertexShader, SimpleFragmentShader);

}


Model::~Model() {


}



void Model::render(const Mtx44& transform) {

    cross::RenderSystem::resetBufferBind();

    current_shader_->use();
    current_shader_->setUniform(SHADER_UNIF_PMV, transform);


    mesh_->vertexBuffer().bind();
    mesh_->indexBuffer().bind();

    //  頂点座標有効化
    current_shader_->setEnableAttributeArray(SHADER_ATTR_POSITION, true);
    current_shader_->setAttributePointer(
        SHADER_ATTR_POSITION,
        3,
        cross::RenderSystem::FLOAT,
        false,
        sizeof(VertexP3N),
        0
    );

    //  頂点法線有効化
    current_shader_->setEnableAttributeArray(SHADER_ATTR_NORMAL, true);
    current_shader_->setAttributePointer(
        SHADER_ATTR_NORMAL,
        3,
        cross::RenderSystem::FLOAT,
        false,
        sizeof(VertexP3N),
        (void*)(sizeof(t3::Vec3))
    );

    cross::RenderSystem::drawElements(
        cross::RenderSystem::DrawMode::MODE_TRIANGLES,
        mesh_->indexCount(),
        sizeof(uint32_t)
    );

}





}   // inline namespace gfx
}   // namespace t3

