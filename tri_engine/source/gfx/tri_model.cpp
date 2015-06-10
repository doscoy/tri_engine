
#include "gfx/tri_model.hpp"
#include "gfx/tri_vertex_types.hpp"
#include "kernel/memory/tri_new.hpp"
#include "../shader/tri_simple3d.vsh"
#include "../shader/tri_simple3d.fsh"
#include "../shader/tri_model.vsh"
#include "../shader/tri_model.fsh"

namespace  {


const char* SHADER_ATTR_POSITION = "a_position";
const char* SHADER_ATTR_NORMAL = "a_normal";
const char* SHADER_ATTR_UV = "a_uv";
const char* SHADER_UNIF_PMV = "u_mvp";
const char* SHADER_UNIF_SHADOW_MTX = "u_shadow_mtx";
const char* SHADER_UNIF_SAMPLER = "sampler";
const char* SHADER_UNIF_SHADOW_SAMPLER = "shadow_samp";
const char* SHADER_OUT_COLOR = "FragColor";

}


namespace t3 {



Model::Model()
    : mesh_(nullptr)
    , default_shader_()
    , current_shader_(&default_shader_)
    , shadow_cast_(false)
{

    //  シェーダ作成
    default_shader_.build(model_vsh, model_fsh);

}


Model::~Model() {


}



//void Model::render(const Mtx44& transform) {
void Model::render(const RenderInfo& info) {

    if (info.renderMode() == RenderInfo::SHADOW) {
        if (!shadow_cast_) {
            return;
        }
    }

    cross::RenderSystem::resetBufferBind();
    mesh_->bind();

    current_shader_->use();
    current_shader_->setUniform(SHADER_UNIF_PMV, *info.transform());
    current_shader_->setUniform(SHADER_UNIF_SAMPLER, 0);
    current_shader_->setUniform(SHADER_UNIF_SHADOW_SAMPLER, 1);
    
    //  影用行列生成
    Mtx44 shadow_bias;
    Mtx44::makeShadowBias(shadow_bias);
    
    Mtx44 shadow_mtx;
    shadow_mtx = shadowBias * info.projection() * info.lightMatrix();
    
    current_shader_->setUniform(SHADER_UNIF_SHADOW_MTX, shadow_mtx);
    
    default_shader_.bindAttributeLocation(0, SHADER_ATTR_POSITION);
    default_shader_.bindAttributeLocation(1, SHADER_ATTR_NORMAL);
    default_shader_.bindAttributeLocation(2, SHADER_ATTR_UV);
    default_shader_.bindFragmentDataLocation(0, SHADER_OUT_COLOR);


    cross::RenderSystem::setActiveTextureUnit(
        cross::RenderSystem::TextureUnit::UNIT0
    );
    auto& material = mesh_->material();
    material->texture()->bind();
    
    cross::RenderSystem::setActiveTextureUnit(
        cross::RenderSystem::TextureUnit::UNIT1
    );
    info.shadowTexture()->bind();


    cross::RenderSystem::setCullingMode(culling_mode_);

    cross::RenderSystem::drawElements(
        cross::RenderSystem::DrawMode::MODE_TRIANGLES,
        mesh_->indexCount(),
        sizeof(uint32_t)
    );
    mesh_->unbind();
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

