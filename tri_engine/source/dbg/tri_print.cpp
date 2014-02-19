//
//  tri_print.cpp
//  gl_1
//
//  Created by 可児 哲郎 on 12/01/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "tri_print.hpp"

#include <stdio.h>
#include <stdarg.h>

#include "base/tri_screen.hpp"
#include "dbg/tri_assert.hpp"
#include "gfx/tri_resource_manager.hpp"
#include "gfx/tri_texture.hpp"
#include "gfx/tri_texture_factory.hpp"
#include "gfx/tri_render_system.hpp"
#include "base/tri_game_system.hpp"
#include "tri_debug_string_layer.hpp"
#include "kernel/tri_kernel.hpp"

// .cpp
#include "tri_debug_font_data.cpp"


namespace {

constexpr int BUFFER_LENGTH = 256;
std::shared_ptr<t3::Texture> debugfont_ = nullptr;
t3::DebugStringLayer dbg_screen_layer_;


}   //  unname namespace



void beginPrint(
    const float w,
    const float h
){
    t3::Mtx4 projection_mtx;
    projection_mtx.ortho(0, w, h, 0, 0, 1);
    t3::RenderSystem::setProjectionMatrix(projection_mtx);
    
    t3::Mtx4 world_mtx;
    world_mtx.identity();
    t3::RenderSystem::setWorldTransformMatrix(world_mtx);
    
    //  テクスチャの割り当て
    t3::RenderSystem::setTexture(debugfont_);
    
    t3::RenderSystem::setTextureMinFilter(t3::RenderSystem::TextureFilterType::TYPE_NEAREST);
    t3::RenderSystem::setTextureMagFilter(t3::RenderSystem::TextureFilterType::TYPE_NEAREST);

    t3::RenderSystem::setBlendFunctionType(
        t3::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        t3::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );
    
    t3::RenderSystem::setBlend(true);

    
    t3::RenderSystem::setTextureMapping(true);
    t3::RenderSystem::setCulling(false);
    
}
void endPrint()
{
    t3::RenderSystem::setTextureMapping(false);
    t3::RenderSystem::setBlend(false);
}

void debugFontPrint(
    const char c,
    const int x,
    const int y,
    const t3::rgba32_t color,
    const int font_pixel_size
){
    char char_idx = c - '!' + 1;


    constexpr int font_size = 16;
    int width_num = debugfont_->getWidth() / font_size;
    int tex_x = (char_idx % width_num) * font_size;
    int tex_y = (char_idx / width_num) * font_size;
    
    float dbg_font_tex_width = static_cast<float>(debugfont_->getWidth());
    float dbg_font_tex_height = static_cast<float>(debugfont_->getHeight());
    
    float u0 = static_cast<float>(tex_x) / dbg_font_tex_width;
    float v0 = static_cast<float>(tex_y) / dbg_font_tex_height;
    
    float u1 = static_cast<float>(tex_x + font_size) / dbg_font_tex_width;
    float v1 = static_cast<float>(tex_y + font_size) / dbg_font_tex_height;
    
    float x0 = (x);
    float x1 = (x+font_pixel_size);
    float y0 = (y);
    float y1 = (y+font_pixel_size);
    
    
    uint8_t cr = (color & 0xFF000000) >> 24;
    uint8_t cg = (color & 0x00FF0000) >> 16;
    uint8_t cb = (color & 0x0000FF00) >> 8;
    uint8_t ca = (color & 0x000000FF) >> 0;


    t3::Color drawcolor(cr, cg, cb, ca);
    t3::RenderSystem::drawQuad(
        t3::Vec3(x0, y0, 0),
        t3::Vec3(x0, y1, 0),
        t3::Vec3(x1, y1, 0),
        t3::Vec3(x1, y0, 0),
        drawcolor,
        u0, v0, u1, v1
    );
}

namespace t3 {
inline namespace dbg {

void initializeDebugPrint()
{

    
    debugfont_ = TextureFactory::createFromData(
        "debugfont",
        dbg_font_.width_,
        dbg_font_.height_,
        RenderSystem::ColorFormat::RGBA,
        dbg_font_.pixel_data_
    );

    T3_NULL_ASSERT(debugfont_);
    
    //  デバッグレイヤーを登録
    GameSystem& gs = GameSystem::getInstance();
    gs.attachLayer(dbg_screen_layer_);
    
}


void printDisplay(
    const float x,
    const float y,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[BUFFER_LENGTH];
    vsnprintf(buf, BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    dbg_screen_layer_.writeString(
        x,
        y,
        Color::magenta().getRGBA(),
        DEBUG_FONT_POINT,
        buf
    );
}

void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[BUFFER_LENGTH];
    vsnprintf(buf, BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    dbg_screen_layer_.writeString(
        x,
        y,
        color.getRGBA(),
        DEBUG_FONT_POINT,
        buf
    );
}
  
void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const int size,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[BUFFER_LENGTH];
    vsnprintf(buf, BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    dbg_screen_layer_.writeString(
        x,
        y,
        color.getRGBA(),
        size,
        buf
    );
}




}   // inline namespace dbg
}   // namespace t3

