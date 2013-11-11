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

#include "../kernel/tri_screen.hpp"
#include "../dbg/tri_assert.hpp"
#include "../gfx/tri_resource_manager.hpp"
#include "../gfx/tri_texture.hpp"
#include "../gfx/tri_texture_factory.hpp"
#include "../kernel/tri_game_system.hpp"
#include "tri_debug_string_layer.hpp"
#include "../io/tri_filepath.hpp"

namespace {

constexpr int BUFFER_LENGTH = 256;

std::shared_ptr<t3::Texture> debugfont_ = nullptr;

const char* DEBUG_FONT_PATH = "font1.png";

t3::DebugStringLayer dbg_screen_layer_;




}   //  unname namespace



void beginPrint(
    const float w,
    const float h
){
    ogl::matrixMode(GL_PROJECTION);
    ogl::pushMatrix();
    ogl::loadIdentity();
    ogl::ortho(0, w, h, 0, -1.0, 1.0);
    ogl::matrixMode(GL_MODELVIEW);
    ogl::pushMatrix();
    ogl::loadIdentity();
    
    //  テクスチャ画像はバイト単位に詰め込まれている
    ogl::pixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    
    //  テクスチャの割り当て
    ogl::texImage2d(
                 GL_TEXTURE_2D,
                 0,
                 debugfont_->getColorFormat(),
                 debugfont_->getWidth(),
                 debugfont_->getHeight(),
                 0,
                 debugfont_->getColorFormat(),
                 GL_UNSIGNED_BYTE,
                 debugfont_->getData()
                 );
    
    ogl::texParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ogl::texParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    ogl::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ogl::enable(GL_BLEND);
    
    GLfloat env_color[] = { 1, 1, 0, 1 };
    ogl::materialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, env_color );
    ogl::enable( GL_TEXTURE_2D );
    ogl::disable(GL_CULL_FACE);
    
    ogl::normal3d( 0, 0, 1 );
    
}
void endPrint()
{
    ogl::disable(GL_TEXTURE_2D);
    ogl::disable(GL_BLEND);
}


void debugFontPrint(
    const char c,
    const int x,
    const int y,
    const uint32_t color,
    const int font_pixel_size
){
    constexpr int font_size = 32;
    int width_num = debugfont_->getWidth() / font_size;
    int tex_x = (c % width_num) * font_size;
    int tex_y = (c / width_num) * font_size;
    
    float u0 = static_cast<float>(tex_x) / static_cast<float>(debugfont_->getWidth() );
    float v0 = static_cast<float>(tex_y) / static_cast<float>(debugfont_->getHeight() );
    
    float u1 = static_cast<float>(tex_x + font_size) / static_cast<float>( debugfont_->getWidth() );
    float v1 = static_cast<float>(tex_y + font_size) / static_cast<float>( debugfont_->getHeight() );
    
    float x0 = (x);
    float x1 = (x+font_pixel_size);
    float y0 = (y);
    float y1 = (y+font_pixel_size);
    
    
    uint8_t cr = (color & 0xFF000000) >> 24;
    uint8_t cg = (color & 0x00FF0000) >> 16;
    uint8_t cb = (color & 0x0000FF00) >> 8;
    uint8_t ca = (color & 0x000000FF) >> 0;

    ogl::begin( GL_QUADS );
    
    //  左上
    
    ogl::color4ub( cr, cg, cb, ca );
    ogl::texCoord2f( u0, v0 );
    ogl::vertex3f(x0, y0, 0);
    
    //  左下w
    ogl::color4ub( cr, cg, cb, ca );
    ogl::texCoord2f(u0, v1);
    ogl::vertex3f(x0, y1, 0);
    
    //  右下
    ogl::color4ub( cr, cg, cb, ca );
    ogl::texCoord2f(u1, v1);
    ogl::vertex3f(x1, y1, 0);
    
    //  右上
    ogl::color4ub( cr, cg, cb, ca );
    ogl::texCoord2f(u1, v0);
    ogl::vertex3f(x1, y0, 0);
    
    
    
    ogl::end();
    
}

namespace t3 {
inline namespace dbg {

void initializeDebugPrint()
{
    //  デバッグフォントのテクスチャを読み込み
    FilePath font_path(DEBUG_FONT_PATH);
    debugfont_ = TextureFactory::createFromFile(font_path.getFullPath());
    T3_NULL_ASSERT( debugfont_ );
    
    //  デバッグレイヤーを登録
    GameSystem& gs = GameSystem::getInstance();
    gs.attachLayer( dbg_screen_layer_ );
    
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
    
    dbg_screen_layer_.writeString(x, y, Color::magenta().getRGBA(), buf);
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
    
    dbg_screen_layer_.writeString(x, y, color.getRGBA(), buf);
}




}   // inline namespace dbg
}   // namespace t3

