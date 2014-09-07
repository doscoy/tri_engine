
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
    
        glBindTexture(GL_TEXTURE_2D, texture_->id());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            T3_ASSERT(glGetError() == GL_NO_ERROR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            0
        );
        T3_TRACE_VALUE(width);
        T3_TRACE_VALUE(height);

    
    
    
    
    
    
    GL_CHECK();
    
    //  デプスバッファ作成
    glGenRenderbuffers(1, &depth_);
    GL_CHECK();
    glBindRenderbuffer(GL_RENDERBUFFER, depth_);
    GL_CHECK();
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT16,
        width,
        height
    );
    GL_CHECK();
    
    //  フレームバッファ作成
    glGenFramebuffers(1, &fb_);
    GL_CHECK();
    glBindFramebuffer(GL_FRAMEBUFFER, fb_);
    GL_CHECK();
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,   //  カラーバッファとして設定
        GL_TEXTURE_2D,
        texture_->id(),
        0
    );
    GL_CHECK();
    
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,    //  デブスバッファとして設定
        GL_RENDERBUFFER,
        depth_
    );
    GL_CHECK();
    
    glBindFramebuffer(GL_FRAMEBUFFER, default_fb);
    glBindRenderbuffer(GL_RENDERBUFFER, default_rb);
    GL_CHECK();
    
}

Surface::~Surface() {
    glDeleteFramebuffers(1, &fb_);
    glDeleteRenderbuffers(1, &depth_);
}


void Surface::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fb_);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_);
}

}   // namespace gfx
}   // namespace t3


