
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
    , color_texture_()
    , depth_texture_()
    , bound_(false)
{
    
    //  オフスクリーン用のテクスチャ
    color_texture_ = Texture::create(
        "sfcc",
        static_cast<int>(width),
        static_cast<int>(height),
        cross::RenderSystem::ColorFormat::RGBA,
        cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
        nullptr
    );

    depth_texture_ = Texture::create(
        "dsfd",
        static_cast<int>(width),
        static_cast<int>(height),
        cross::RenderSystem::ColorFormat::DEPTH,
        cross::RenderSystem::TypeFormat::UNSIGNED_SHORT,
        nullptr
    );
    
    depth_texture_->bind();
    cross::RenderSystem::setTextureBorderColor(1, 0, 0, 0);
    cross::RenderSystem::bindTexture(0);
  
    cross::RenderSystem::setActiveTextureUnit(0);
    depth_texture_->bind();


    
    
    //  フレームバッファ作成
    cross::RenderSystem::createFrameBuffer(&fb_);
    cross::RenderSystem::bindFrameBuffer(fb_);

//    cross::RenderSystem::setDrawBuffer(cross::RenderSystem::DrawBufferTarget::NONE);

    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::COLOR0,
        color_texture_->id()
    );

    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::DEPTH,
        depth_texture_->id()
    );
    
    cross::RenderSystem::bindFrameBuffer(0);
}

Surface::~Surface() {
    cross::RenderSystem::deleteFrameBuffer(&fb_);
}


void Surface::bind() {

    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);
    cross::RenderSystem::setDepthTest(true);

    cross::RenderSystem::bindFrameBuffer(fb_);
    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);
    cross::RenderSystem::setDepthTest(true);


    T3_ASSERT(!bound_);
    bound_ = true;
}

void Surface::clear() {
//    if (color_texture_->getColorFormat() == cross::RenderSystem::ColorFormat::DEPTH) {
//        cross::RenderSystem::clearBuffer(false, true, false);
//    }
//    else {
        cross::RenderSystem::clearBuffer(true, true, false);
    
//    }

}


void Surface::unbind() {
    T3_ASSERT(bound_);
    bound_ = false;
    cross::RenderSystem::bindFrameBuffer(0);

}


void Surface::preRender() {

    bind();
    clear();

    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);

    if (color_texture_->getColorFormat() == cross::RenderSystem::ColorFormat::DEPTH) {
    //    cross::RenderSystem::colorMask(false, false, false, false);
    }

}


void Surface::postRender() {
    if (color_texture_->getColorFormat() == cross::RenderSystem::ColorFormat::DEPTH) {
    //    cross::RenderSystem::colorMask(true, true, true, true);
    }
    unbind();
}

}   // namespace t3


