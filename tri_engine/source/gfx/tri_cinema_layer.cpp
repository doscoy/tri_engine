


#include "gfx/tri_cinema_layer.hpp"
#include "../shader/tri_simple_tex.fsh"
#include "../shader/tri_simple_tex.vsh"
#include "../shader/tri_show_depth_tex.fsh"
#include "gfx/tri_vertex_types.hpp"


namespace t3 {
  


CinemaLayer::CinemaLayer()
    : CinemaLayer("cinema", RenderLayer::PRIORITY_APP_FRONT1)
{}


CinemaLayer::CinemaLayer(
    const String& name,
    const int priority
)   : RenderLayer(name, priority)
    , shader_(nullptr)
    , color_shader_(nullptr)
    , depth_shader_(nullptr)
    , texture_(nullptr)
{

    //  デフォルトのカラーシェーダ作成
    color_shader_ = Shader::create(simple_tex_vsh, simple_tex_fsh);
    color_shader_->use();
    color_shader_->bindAttributeLocation(0, "a_position");
    color_shader_->bindAttributeLocation(1, "a_uv");
    color_shader_->bindFragmentDataLocation(0, "FragColor");

    //  デフォルトのデプスシェーダ作成
    depth_shader_ = Shader::create(simple_tex_vsh, show_depth_tex_fsh);
    depth_shader_->use();
    depth_shader_->bindAttributeLocation(0, "a_position");
    depth_shader_->bindAttributeLocation(1, "a_uv");
    depth_shader_->bindFragmentDataLocation(0, "FragColor");
    
    //  デフォルトシェーダを設定
    useDefaultColorShader();
    
    
    vao_ = cross::RenderSystem::createVertexArrayObject();
    cross::RenderSystem::bindVertexArrayObject(vao_);

    vb_.bind();
    
    VertexP2T varray[] = {
    //     x, y,     u,  v
        {{0, 0}, {0, 0}},
        {{0,  1}, {0, 1}},
        {{ 1, 0}, {1, 0}},
        {{ 1,  1}, {1, 1}}
    };
    
    cross::RenderSystem::setupBufferData(
        cross::RenderSystem::BufferType::TYPE_VERTEX,
        sizeof(VertexP2T) * 4,
        varray,
        cross::RenderSystem::BufferUsage::STATIC_DRAW
    );
    
    constexpr int POSITION_SLOT = 0;
    constexpr int UV_SLOT = 1;


    //  座標有効化
    cross::RenderSystem::setEnableVertexAttribute(POSITION_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        POSITION_SLOT,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VertexP2T),
        0
    );


    //  UV有効化
    cross::RenderSystem::setEnableVertexAttribute(UV_SLOT);
    cross::RenderSystem::setVertexAttributePointer(
        UV_SLOT,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        sizeof(VertexP2T),
        (void*)offsetof(VertexP2T, uv_)
    );


    cross::RenderSystem::bindVertexArrayObject(0);
}


CinemaLayer::~CinemaLayer() {
    cross::RenderSystem::deleteVertexArrayBuffer(vao_);
}


void CinemaLayer::updateLayer(tick_t delta_time) {


}


void CinemaLayer::drawLayer() {
    
    if (!texture_) {
        return;
    }
    
    cross::RenderSystem::setViewport(-256, -256, 512, 512);
    
    cross::RenderSystem::resetBufferBind();
    cross::RenderSystem::bindVertexArrayObject(vao_);
    
    cross::RenderSystem::setCulling(false);
    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);
    cross::RenderSystem::setDepthTest(true);
//    cross::RenderSystem::setBlendMode(cross::RenderSystem::BlendMode::NONE);

    // シェーダで描画
    bool use_result = shader_->use();
    T3_ASSERT(use_result);
    

    //頂点配列を有効化
    shader_->setUniform("sampler", 0);
    cross::RenderSystem::setActiveTextureUnit(0);
    texture_->bind();
    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);
    cross::RenderSystem::setDepthTest(true);
    
    
    cross::RenderSystem::drawArray(
        cross::RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        0,
        4
    );
    cross::RenderSystem::bindVertexArrayObject(0);

}




}   //  namespace t3
