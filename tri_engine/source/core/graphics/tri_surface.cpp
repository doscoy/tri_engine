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




Surface::Surface()
    : Surface(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT, Type::COLOR_DEPTH)
{
}


Surface::Surface(
    float width,
    float height,
    Type type
)   : size_(width, height)
    , fb_()
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

Surface::~Surface() {

}


void Surface::bind() {

    fb_.bind();
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
    fb_.unbind();
}


void Surface::preRender() {
    //  フレームバッファ接続
    bind();
    clear();
    
    cross::RenderSystem::getViewport(
        &last_viewport_pos_x_,
        &last_viewport_pos_y_,
        &last_viewport_width_,
        &last_viewport_height_
    );
    
    cross::RenderSystem::setViewport(0, 0, size_.x_, size_.y_);
}


void Surface::postRender() {


    cross::RenderSystem::setViewport(
        last_viewport_pos_x_,
        last_viewport_pos_y_,
        last_viewport_width_,
        last_viewport_height_
    );

    //  フレームバッファへの接続解除
    unbind();
}

TRI_CORE_NS_END


