
#include "tri_surface.hpp"
#include "platform/platform_sdk.hpp"


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
    , depth_(0)
    , texture_()
{
    GLint default_fb;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &default_fb);
    
    GLint default_rb;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &default_rb);

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
    
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_RGBA4,
        width,
        height
    );
    
    
    
    //  デプスバッファ作成
    RenderSystem::createRenderBuffer(&depth_);
    RenderSystem::bindRenderBuffer(depth_);
    
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT16,
        width,
        height
    );
    
    
    
    //  フレームバッファ作成
    RenderSystem::createFrameBuffer(&fb_);
    RenderSystem::bindFrameBuffer(fb_);

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,    //  デブスバッファとして設定
        GL_RENDERBUFFER,
        cb_
    );
    
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,    //  デブスバッファとして設定
        GL_RENDERBUFFER,
        depth_
    );

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,   //  カラーバッファとして設定
        GL_TEXTURE_2D,
        texture_->id(),
        0
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
    RenderSystem::bindFrameBuffer(fb_);
    RenderSystem::bindRenderBuffer(cb_);
}

}   // namespace gfx
}   // namespace t3


