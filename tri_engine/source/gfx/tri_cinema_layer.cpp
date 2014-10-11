


#include "gfx/tri_cinema_layer.hpp"
#include "../shader/tri_simple_tex.fsh"
#include "../shader/tri_simple_tex.vsh"



namespace t3 {
  


CinemaLayer::CinemaLayer()
    : CinemaLayer("cinema", RenderLayer::PRIORITY_APP_FRONT1)
{
}


CinemaLayer::CinemaLayer(
    const String& name,
    const int priority
)   : RenderLayer(name, priority)
    , shader_(nullptr)
    , default_shader_(nullptr)
    , texture_(nullptr)
{

    //  デフォルトシェーダ作成
    default_shader_ = std::make_shared<Shader>();
    default_shader_->compileShaderFromString(simple_tex_vsh, RenderSystem::ShaderType::VERTEX_SHADER);
    default_shader_->compileShaderFromString(simple_tex_fsh, RenderSystem::ShaderType::FRAGMENT_SHADER);
    bool shader_link_result = default_shader_->link();
    T3_ASSERT(shader_link_result);

    //  デフォルトシェーダを設定
    shader_ = default_shader_;
}

CinemaLayer::~CinemaLayer() {

}


void CinemaLayer::updateLayer(tick_t delta_time) {


}


void CinemaLayer::drawLayer() {
    
    RenderSystem::resetBufferBind();
    
    if (!texture_) {
        return;
    }
    
    T3_ASSERT(shader_);
    
    RenderSystem::setBlendMode(RenderSystem::BlendMode::NONE);

    // シェーダで描画
    bool use_result = shader_->use();
    T3_ASSERT(use_result);
    int position_slot = shader_->getAttributeLocation("a_position");
    T3_ASSERT(position_slot >= 0);
    int uv_slot = shader_->getAttributeLocation("a_uv");
    T3_ASSERT(uv_slot >= 0);
    
    float x0 = -1.0f;
    float x1 = 1.0f;
    float y0 = -1.0f;
    float y1 = 1.0f;
    
    float u0 = 0.0f;
    float u1 = 1.0f;
    float v0 = 0.0f;
    float v1 = 1.0f;
    
    float varray[] = {
        x0, y0,
        x0, y1,
        x1, y0,
        x1, y1
    };
    float vuv[] = {
        u0, v0,
        u0, v1,
        u1, v0,
        u1, v1
    };
    t3::RenderSystem::setEnableVertexAttribute(position_slot);
    t3::RenderSystem::setEnableVertexAttribute(uv_slot);

    //頂点配列を有効化
    shader_->setUniform("sampler", 0);

    texture_->bind();
    t3::RenderSystem::setVertexAttributePointer(
        position_slot,
        2,
        GL_FLOAT,
        false,
        0,
        varray
    );
    t3::RenderSystem::setVertexAttributePointer(
        uv_slot,
        2,
        GL_FLOAT,
        false,
        0,
        vuv
    );
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}




}   //  namespace t3
