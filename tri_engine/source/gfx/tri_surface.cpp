
#include "gfx/tri_surface.hpp"

#include "base/tri_director.hpp"


namespace t3 {



void GL_CHECK() {

    T3_ASSERT(cross::RenderSystem::isError());
}

Surface::Surface()
    : Surface(t3::Director::VIRTUAL_SCREEN_WIDTH, t3::Director::VIRTUAL_SCREEN_HEIGHT)
{
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

    cross::RenderSystem::FrameBufferID default_fb = cross::RenderSystem::getCurrentFrameBufferID();
    cross::RenderSystem::RenderBufferID default_rb = cross::RenderSystem::getCurrentRenderBufferID();
    
    //  オフスクリーン用のテクスチャ
    texture_ = t3::Texture::create(
        "sfc",
        width,
        height,
        cross::RenderSystem::ColorFormat::RGBA
    );
    texture_->bind();
    
    
    
    
    //  カラーバッファ作成
    cross::RenderSystem::createRenderBuffer(&cb_);
    cross::RenderSystem::bindRenderBuffer(cb_);
    
    cross::RenderSystem::setupRenderBufferStorage(
        cross::RenderSystem::RenderBufferUsage::COLOR,
        width,
        height
    );
    
    
    
    //  デプスバッファ作成
    cross::RenderSystem::createRenderBuffer(&depth_);
    cross::RenderSystem::bindRenderBuffer(depth_);
    
    cross::RenderSystem::setupRenderBufferStorage(
        cross::RenderSystem::RenderBufferUsage::DEPTH,
        width,
        height
    );
    
    
    //  フレームバッファ作成
    cross::RenderSystem::createFrameBuffer(&fb_);
    cross::RenderSystem::bindFrameBuffer(fb_);
    cross::RenderSystem::attachRenderBuffer(
        cross::RenderSystem::RenderBufferAttachType::COLOR0,
        cb_
    );

    cross::RenderSystem::attachRenderBuffer(
        cross::RenderSystem::RenderBufferAttachType::DEPTH,
        depth_
    );
    
    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::COLOR0,
        texture_->id()
    );

    cross::RenderSystem::bindFrameBuffer(default_fb);
    cross::RenderSystem::bindRenderBuffer(default_rb);
    
    
}

Surface::~Surface() {
    cross::RenderSystem::deleteFrameBuffer(&fb_);
    cross::RenderSystem::deleteRenderBuffer(&depth_);
    cross::RenderSystem::deleteRenderBuffer(&cb_);
}


void Surface::bind() {

    last_fb_ = cross::RenderSystem::getCurrentFrameBufferID();
    last_rb_ = cross::RenderSystem::getCurrentRenderBufferID();

    cross::RenderSystem::bindFrameBuffer(fb_);
    cross::RenderSystem::bindRenderBuffer(cb_);
}

void Surface::clear() {

    cross::RenderSystem::clearBuffer(true, true, false);

}


void Surface::unbind() {
    T3_ASSERT(last_fb_ != 0);
    T3_ASSERT(last_rb_ != 0);
    cross::RenderSystem::bindFrameBuffer(last_fb_);
    cross::RenderSystem::bindRenderBuffer(last_rb_);

}


}   // namespace t3


