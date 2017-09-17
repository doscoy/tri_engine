////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/surface/tri_surface.hpp"
#include "core/base/tri_screen_manager.hpp"
#include "core/base/tri_director.hpp"


TRI_CORE_NS_BEGIN

///
/// コンストラクタ
Surface::Surface(float width, float height)
    : textures_()
    , size_(width, height)
{}


///
/// 描画後処理
void Surface::preRender() {
    onPreRender();
}

///
/// 描画後処理
void Surface::postRender() {
    onPostRender();
}


FrameBufferSurface::FrameBufferSurface(
    float width,
    float height
)   : Surface(width, height)
    , last_viewport_pos_x_(0)
    , last_viewport_pos_y_(0)
    , last_viewport_width_(0)
    , last_viewport_height_(0)
    , fb_()
    , bound_(false)
    , buffer_cleared_(false)
{
}

void FrameBufferSurface::onInitialize() {
    //  テクスチャ作成
    createTexture();
    
    //  フレームバッファにテクスチャをアタッチ
    fb_.bind();

    attachTexture();
    
    cross::RenderSystem::bindTexture(0);
    cross::RenderSystem::setActiveTextureUnit(0);

    fb_.unbind();
}


void FrameBufferSurface::bind() {

    fb_.bind();
    T3_ASSERT(!bound_);
    bound_ = true;
}


void FrameBufferSurface::clearSurface() {
    bind();
    clearSurfaceCore();
    unbind();
}


void FrameBufferSurface::unbind() {
    T3_ASSERT(bound_);
    bound_ = false;
    fb_.unbind();
}

void FrameBufferSurface::setupViewport() {

    cross::RenderSystem::getViewport(
        &last_viewport_pos_x_,
        &last_viewport_pos_y_,
        &last_viewport_width_,
        &last_viewport_height_
    );
    
    cross::RenderSystem::setViewport(
        0, 
        0, 
        static_cast<int>(size_.x_), 
        static_cast<int>(size_.y_)
    );

}


void FrameBufferSurface::resetViewport() {

    cross::RenderSystem::setViewport(
        last_viewport_pos_x_,
        last_viewport_pos_y_,
        last_viewport_width_,
        last_viewport_height_
    );

}

///
/// 描画前処理
void FrameBufferSurface::onPreRender() {
    //  フレームバッファ接続
    bind();
    setupViewport();
}

///
/// 描画後処理
void FrameBufferSurface::onPostRender() {
    resetViewport();
    //  フレームバッファへの接続解除
    unbind();
}

///////////////////////////////////////////////////////////////

///
/// デバイス用サーフェス
DeviceSurface::DeviceSurface()
    : Surface(100,100)
{
}

///
/// 初期化
void DeviceSurface::onInitialize() {
    auto& screen = ScreenManager::instance();
    size_ = screen.deviceScreenSize();
}

///////////////////////////////////////////////////////////////

///
/// コンストラクタ
DepthSurface::DepthSurface(
    float width, float height
)   : FrameBufferSurface(width, height)
{}

///
/// テクスチャ生成
void DepthSurface::createTexture() {

    //  デプステクスチャ
    depth_texture_ = Texture::create(
        "dsfd",
        static_cast<int>(size_.x_),
        static_cast<int>(size_.y_),
        cross::RenderSystem::ColorFormat::DEPTH,
        cross::RenderSystem::TypeFormat::UNSIGNED_SHORT,
        nullptr
    );

    depth_texture_->bind();
    cross::RenderSystem::setTextureBorderColor(1, 0, 0, 0);

}

///
/// テクスチャをアタッチする
void DepthSurface::attachTexture() {

    //  デプステクスチャをアタッチ
    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::DEPTH,
        depth_texture_->id()
    );

}

///
/// サーフェスクリア
void DepthSurface::clearSurfaceCore() {
    //  デプス値のみクリア
    cross::RenderSystem::clearBuffer(false, true, false);
}


///////////////////////////////////////////////////////////////

///
/// コンストラクタ
ColorDepthSurface::ColorDepthSurface(
    float width, float height
)   : FrameBufferSurface(width, height)
{}

///
/// テクスチャ生成
void ColorDepthSurface::createTexture() {
    //  カラーテクスチャ
    color_texture_ = Texture::create(
        "sfcc",
        static_cast<int>(width()),
        static_cast<int>(height()),
        cross::RenderSystem::ColorFormat::RGBA,
        cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
        nullptr
    );

    //  デプステクスチャ
    depth_texture_ = Texture::create(
        "dsfd",
        static_cast<int>(width()),
        static_cast<int>(height()),
        cross::RenderSystem::ColorFormat::DEPTH,
        cross::RenderSystem::TypeFormat::UNSIGNED_SHORT,
        nullptr
    );

    depth_texture_->bind();
    cross::RenderSystem::setTextureBorderColor(1, 0, 0, 0);
    cross::RenderSystem::bindTexture(0);
  
    cross::RenderSystem::setActiveTextureUnit(0);

}

///
/// テクスチャをアタッチする
void ColorDepthSurface::attachTexture() {
    //  カラーテクスチャを接続
    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::COLOR0,
        color_texture_->id()
    );

    //  デプステクスチャをアタッチ
    cross::RenderSystem::attachFrameBufferTexture(
        cross::RenderSystem::RenderBufferAttachType::DEPTH,
        depth_texture_->id()
    );

}

///
/// サーフェスクリア
void ColorDepthSurface::clearSurfaceCore() {
    //  カラーとデプスクリア
    cross::RenderSystem::clearBuffer(true, true, false);
}


///
/// サーフェスクリア
void DeviceSurface::clearSurface() {
    //  カラーとデプスクリア
    cross::RenderSystem::clearBuffer(true, true, false);
}

TRI_CORE_NS_END


