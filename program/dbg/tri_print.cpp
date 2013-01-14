//
//  tri_print.cpp
//  gl_1
//
//  Created by 可児 哲郎 on 12/01/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "tri_print.hpp"

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdarg.h>

#include "../kernel/tri_screen.hpp"
#include "../dbg/tri_assert.hpp"
#include "../gfx/tri_resource_manager.hpp"
#include "../gfx/tri_texture.hpp"
#include "../gfx/tri_texture_factory.hpp"
#include "../kernel/tri_game_system.hpp"

namespace {

constexpr int BUFFER_LENGTH = 256;

const t3::Texture* debugfont_ = nullptr;

const char* DEBUG_FONT_PATH = "/Users/doscoy_t/project/tri_sandbox_osx/tri_sandbox_osx/resource/font2.png";
//const char* DEBUG_FONT_PATH = "/Users/kani/project/tri_sandbox/dev_t3/resource/font1.png";

t3::color_t font_color_( t3::COLOR_WHITE );
int font_size_ = t3::DEBUG_FONT_POINT;

void beginPrint()
{
    const t3::GameSystem* gs = t3::GameSystem::getInstancePointer();
    const t3::ivec2_t& screen_size = gs->getScreenSize();
    float w = screen_size.x;
    float h = screen_size.y;
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //  テクスチャ画像はバイト単位に詰め込まれている
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    
    //  テクスチャの割り当て
    glTexImage2D(
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
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    GLfloat env_color[] = { 1, 1, 0, 1 };
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, env_color );
    glEnable( GL_TEXTURE_2D );
    
    glNormal3d( 0, 0, 1 );
    
}
void endPrint()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void debugFontPrint(const char c, const int x, const int y, const t3::color_t& color, const int font_pixel_size)
{
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
    
    
    glBegin( GL_QUADS );
    
    //  左上
    glColor3ub( color.r, color.g, color.b );
    glTexCoord2d( u0, v0 );
    glVertex3d(x0, y0, 0);
    
    //  左下w
    glColor3ub( color.r, color.g, color.b );
    glTexCoord2d(u0, v1);
    glVertex3d(x0, y1, 0);

    //  右下
    glColor3ub( color.r, color.g, color.b );
    glTexCoord2d(u1, v1);
    glVertex3d(x1, y1, 0);

    //  右上
    glColor3ub( color.r, color.g, color.b );
    glTexCoord2d(u1, v0);
    glVertex3d(x1, y0, 0);
    
    
    
    glEnd();

}



}   //  unname namespace

namespace t3 {
inline namespace dbg {

void initializeDebugPrint()
{
    debugfont_ = TextureFactory::createFromFile( DEBUG_FONT_PATH );
    T3_NULL_ASSERT( debugfont_ );
}
  
void printDisplay( 
    const float x,
    const float y,
    const char* fmt, ... 
){
    va_list arg;
    va_start( arg, fmt );
    
    char buf[BUFFER_LENGTH];
    vsnprintf( buf, BUFFER_LENGTH, fmt, arg );
    va_end( arg );
    
    
    beginPrint();
    
    int pitch = font_size_ - 3;
    int idx = 0;
    char* c = buf;
    while(*c){
        debugFontPrint( *c, x + idx * pitch, y, font_color_, font_size_ );
        ++c;
        ++idx;
    }
    
    endPrint();
}

void printDisplay(
    const float x,
    const float y,
    const color_t& color,
    const char* fmt, ...
){
    va_list arg;
    va_start( arg, fmt );
    
    char buf[BUFFER_LENGTH];
    vsnprintf( buf, BUFFER_LENGTH, fmt, arg );
    va_end( arg );
    
    
    beginPrint();
    
    int pitch = font_size_ - 3;
    int idx = 0;
    char* c = buf;
    while(*c){
        debugFontPrint( *c, x + idx * pitch, y, color, font_size_ );
        ++c;
        ++idx;
    }
    
    endPrint();
}


void setDebugFontColor(
    const color_t& color
){
    font_color_ = color;
}

void setDebugFontSize(
    const int size
){
    font_size_ = size;
}

}   // inline namespace dbg
}   // namespace t3

