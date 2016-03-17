////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/graphics/tri_surface.hpp"

#include "core/base/tri_director.hpp"


TRI_CORE_NS_BEGIN



FrameBufferSurface::FrameBufferSurface(
    float width,
    float height,
    Type type
)   : size_(width, height)
    , last_viewport_pos_x_(0)
    , last_viewport_pos_y_(0)
    , last_viewport_width_(0)
    , last_viewport_height_(0)
    , fb_()
    , color_texture_()
    , depth_texture_()
    , bound_(false)
    , buffer_cleared_(false)
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
            static_cast<int>(size_.x_),
            static_cast<int>(size_.y_),
            cross::RenderSystem::ColorFormat::DEPTH,
            cross::RenderSystem::TypeFormat::UNSIGNED_SHORT,
            nullptr
        );
        depth_texture_->bind();
        cross::RenderSystem::setTextureBorderColor(1, 0, 0, 0);
        cross::RenderSystem::bindTexture(0);
    }
  
    cross::RenderSystem::setActiveTextureUnit(0);



    
    
    //  フレームバッファ作成
    fb_.bind();

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
 
    fb_.unbind();
}



void FrameBufferSurface::bind() {

    fb_.bind();
    T3_ASSERT(!bound_);
    bound_ = true;
}

void FrameBufferSurface::clearBuffer() {
    if (buffer_cleared_) {
        //  既にクリア済のバッファなのでクリアはスキップ
        return;
    }
    
    
    if (type_ == Type::DEPTH_ONLY) {
        cross::RenderSystem::clearBuffer(false, true, false);
    }
    else {
        cross::RenderSystem::clearBuffer(true, true, false);
    }
    
    //  バッファクリア済フラグを立てておく
    buffer_cleared_ = true;
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

void FrameBufferSurface::onBeginRender() {
    buffer_cleared_ = false;
}


void FrameBufferSurface::onPreRender() {
    //  フレームバッファ接続
    bind();
    clearBuffer();
    setupViewport();
}


void FrameBufferSurface::onPostRender() {
    resetViewport();
    //  フレームバッファへの接続解除
    unbind();
}










TRI_CORE_NS_END


