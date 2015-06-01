
#include "gfx/tri_surface.hpp"

#include "base/tri_director.hpp"


namespace t3 {



Surface::Surface()
    : Surface(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT)
{
}


Surface::Surface(
    float width,
    float height
)   : width_(width)
    , height_(height)
    , fb_(0)
    , cb_(0)
    , depth_(0)
    , last_fb_(0)
    , last_rb_(0)
    , texture_()
    , bound_(false)
{

    cross::RenderSystem::FrameBufferID default_fb = cross::RenderSystem::getCurrentFrameBufferID();
    cross::RenderSystem::RenderBufferID default_rb = cross::RenderSystem::getCurrentRenderBufferID();
    
    //  オフスクリーン用のテクスチャ
    texture_ = t3::Texture::create(
        "sfc",
        static_cast<int>(width),
        static_cast<int>(height),
        cross::RenderSystem::ColorFormat::DEPTH
    );

    
    
    
    //  カラーバッファ作成
//    cross::RenderSystem::createRenderBuffer(&cb_);
//    cross::RenderSystem::bindRenderBuffer(cb_);
/*
    cross::RenderSystem::setupRenderBufferStorage(
        cross::RenderSystem::RenderBufferUsage::COLOR,
        static_cast<int>(width),
            static_cast<int>(height)
    );
    
*/    
/*
    //  デプスバッファ作成
    cross::RenderSystem::createRenderBuffer(&depth_);
    cross::RenderSystem::bindRenderBuffer(depth_);
    
    cross::RenderSystem::setupRenderBufferStorage(
        cross::RenderSystem::RenderBufferUsage::DEPTH,
        static_cast<int>(width),
        static_cast<int>(height)
    );
*/  
    
    //  フレームバッファ作成
    cross::RenderSystem::createFrameBuffer(&fb_);
    cross::RenderSystem::bindFrameBuffer(fb_);
/*
    cross::RenderSystem::attachRenderBuffer(
        cross::RenderSystem::RenderBufferAttachType::COLOR0,
        cb_
    );

    cross::RenderSystem::attachRenderBuffer(
        cross::RenderSystem::RenderBufferAttachType::DEPTH,
        depth_
    );
*/
    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::DEPTH,
        texture_->id()
    );

    cross::RenderSystem::bindFrameBuffer(default_fb);
//    cross::RenderSystem::bindRenderBuffer(default_rb);
    
    
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
//    cross::RenderSystem::bindRenderBuffer(cb_);

    T3_ASSERT(!bound_);
    bound_ = true;
}

void Surface::clear() {
    if (texture_->getColorFormat() == cross::RenderSystem::ColorFormat::DEPTH) {
        cross::RenderSystem::clearBuffer(false, true, false);
    }
    else {
        cross::RenderSystem::clearBuffer(true, true, false);
    
    }

}


void Surface::unbind() {
    T3_ASSERT(bound_);
    bound_ = false;
    cross::RenderSystem::bindFrameBuffer(last_fb_);
//    cross::RenderSystem::bindRenderBuffer(last_rb_);

}


void Surface::preRender() {

    bind();
    clear();
    if (texture_->getColorFormat() == cross::RenderSystem::ColorFormat::DEPTH) {
    //    cross::RenderSystem::colorMask(false, false, false, false);
    }

}


void Surface::postRender() {
    if (texture_->getColorFormat() == cross::RenderSystem::ColorFormat::DEPTH) {
    //    cross::RenderSystem::colorMask(true, true, true, true);
    }
    unbind();
}

}   // namespace t3


