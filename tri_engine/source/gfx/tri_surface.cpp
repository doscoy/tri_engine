
#include "gfx/tri_surface.hpp"

#include "base/tri_director.hpp"


namespace t3 {



Surface::Surface()
    : Surface(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT, Type::COLOR_DEPTH)
{
}


Surface::Surface(
    float width,
    float height,
    Type type
)   : width_(width)
    , height_(height)
    , fb_(0)
    , color_texture_()
    , depth_texture_()
    , bound_(false)
    , type_(type)
{
    //  各テクスチャの使用状況
    bool use_color = (type == Type::COLOR_DEPTH || type == Type::COLOR_ONLY);
    bool use_depth = (type == Type::COLOR_DEPTH || type == Type::DEPTH_ONLY);

    //  カラーテクスチャ
    if (use_color) {
        color_texture_ = Texture::create(
            "sfcc",
            static_cast<int>(width),
            static_cast<int>(height),
            cross::RenderSystem::ColorFormat::RGBA,
            cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
            nullptr
        );
    }

    //  デプステクスチャ
    if (use_depth) {
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
    }
  
    cross::RenderSystem::setActiveTextureUnit(0);
//    depth_texture_->bind();


    
    
    //  フレームバッファ作成
    cross::RenderSystem::createFrameBuffer(&fb_);
    cross::RenderSystem::bindFrameBuffer(fb_);

    //  カラーテクスチャを接続
    if (use_color) {
        cross::RenderSystem::attachFrameBufferTexture(
            cross::RenderSystem::RenderBufferAttachType::COLOR0,
            color_texture_->id()
        );
    } else {
        //  カラー値を使わない場合はこのフレームバッファへのカラーの書き込みを停止
        cross::RenderSystem::setDrawBuffer(cross::RenderSystem::DrawBufferTarget::NONE);
    }

    //  デプステクスチャをアタッチ
    if (use_depth) {
        cross::RenderSystem::attachFrameBufferTexture(
            cross::RenderSystem::RenderBufferAttachType::DEPTH,
            depth_texture_->id()
        );
    }
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
    if (type_ == Type::DEPTH_ONLY) {
        cross::RenderSystem::clearBuffer(false, true, false);
    }
    else {
        cross::RenderSystem::clearBuffer(true, true, false);
    }
}


void Surface::unbind() {
    T3_ASSERT(bound_);
    bound_ = false;
    cross::RenderSystem::bindFrameBuffer(0);
}


void Surface::preRender() {
    //  フレームバッファ接続
    bind();
    clear();

    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);

}


void Surface::postRender() {
    //  フレームバッファへの接続解除
    unbind();
}

}   // namespace t3


