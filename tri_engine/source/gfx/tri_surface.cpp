
#include "tri_surface.hpp"
#include "gfx/tri_render_system.hpp"



namespace t3 {
inline namespace gfx {


void GL_CHECK() {
    int err = glGetError();
    T3_ASSERT_MSG(err == GL_NO_ERROR, "err = %d", err);
}


Surface::Surface(
    int width,
    int height
)   : width_(width)
    , height_(height)
    , fb_(0)
    , cb_(0)
    , depth_(0)
    , last_fb_(0)
    , last_rb_(0)
    , texture_()
{

    RenderSystem::FrameBufferID default_fb = RenderSystem::getCurrentFrameBufferID();
    RenderSystem::RenderBufferID default_rb = RenderSystem::getCurrentRenderBufferID();
    
    //  オフスクリーン用のテクスチャ
    texture_ = t3::Texture::create(
        "sfc",
        width,
        height,
        t3::RenderSystem::ColorFormat::RGBA
    );
    
    //  カラーバッファ作成
    RenderSystem::createRenderBuffer(&cb_);
    RenderSystem::bindRenderBuffer(cb_);
    
    RenderSystem::setupRenderBufferStorage(
        RenderSystem::RenderBufferUsage::COLOR,
        width,
        height
    );
    
    
    
    //  デプスバッファ作成
    RenderSystem::createRenderBuffer(&depth_);
    RenderSystem::bindRenderBuffer(depth_);
    
    RenderSystem::setupRenderBufferStorage(
        RenderSystem::RenderBufferUsage::DEPTH,
        width,
        height
    );
    
    
    //  フレームバッファ作成
    RenderSystem::createFrameBuffer(&fb_);
    RenderSystem::bindFrameBuffer(fb_);
    RenderSystem::attachRenderBuffer(
        RenderSystem::RenderBufferAttachType::COLOR0,
        cb_
    );

    RenderSystem::attachRenderBuffer(
        RenderSystem::RenderBufferAttachType::DEPTH,
        depth_
    );
    
    RenderSystem::attachFrameBufferTexture(
        RenderSystem::RenderBufferAttachType::COLOR0,
        texture_->id()
    );

    RenderSystem::bindFrameBuffer(default_fb);
    RenderSystem::bindRenderBuffer(default_rb);
    
    
}

Surface::~Surface() {
    RenderSystem::deleteFrameBuffer(&fb_);
    RenderSystem::deleteRenderBuffer(&depth_);
    RenderSystem::deleteRenderBuffer(&cb_);
}


void Surface::bind() {

    last_fb_ = RenderSystem::getCurrentFrameBufferID();
    last_rb_ = RenderSystem::getCurrentRenderBufferID();

    RenderSystem::bindFrameBuffer(fb_);
    RenderSystem::bindRenderBuffer(cb_);
}

void Surface::unbind() {
    T3_ASSERT(last_fb_ != 0);
    T3_ASSERT(last_rb_ != 0);
    RenderSystem::bindFrameBuffer(last_fb_);
    RenderSystem::bindRenderBuffer(last_rb_);

}


}   // namespace gfx
}   // namespace t3


