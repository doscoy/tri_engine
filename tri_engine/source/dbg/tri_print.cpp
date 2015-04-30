//
//  tri_print.cpp
//  gl_1
//
//  Created by 可児 哲郎 on 12/01/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "dbg/tri_print.hpp"


#include "dbg/tri_assert.hpp"

#include "gfx/tri_texture.hpp"
#include "gfx/tri_texture_factory.hpp"

#include "base/tri_director.hpp"
#include "dbg/tri_debug_string_layer.hpp"
#include "kernel/tri_kernel.hpp"
#include "gfx/tri_shader.hpp"

#include "../shader/tri_font.fsh"
#include "../shader/tri_font.vsh"

// .cpp
#include "tri_debug_font_data.cpp"

namespace {

constexpr int BUFFER_LENGTH = 256;
float width_;
float height_;

t3::Shader font_shader_;

}   //  unname namespace

t3::SharedPtr<t3::Texture> debugfont_ = nullptr;


void beginPrint(
    const float w,
    const float h
){
    width_ = w;
    height_ = h;

    cross::RenderSystem::resetBufferBind();
    debugfont_->bind();

    //  シェーダ切り替え
    bool shader_setup_result = font_shader_.use();
    T3_ASSERT(shader_setup_result);
    
    //  テクスチャの割り当て
    cross::RenderSystem::setActiveTextureUnit(cross::RenderSystem::TextureUnit::UNIT0);
    

    cross::RenderSystem::setBlendFunctionType(
        cross::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        cross::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );
    
    cross::RenderSystem::setBlend(true);
    cross::RenderSystem::setActiveTextureUnit(
        cross::RenderSystem::TextureUnit::UNIT0
    );
    

    
    //  アクティブなサンプラーをステージ０に設定
    font_shader_.setUniform("sampler", 0);
   
}


void endPrint()
{

    cross::RenderSystem::setBlend(false);
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
    int width_num = debugfont_->width() / font_size;
    int tex_x = (char_idx % width_num) * font_size;
    int tex_y = (char_idx / width_num) * font_size;
    
    float dbg_font_tex_width = static_cast<float>(debugfont_->width());
    float dbg_font_tex_height = static_cast<float>(debugfont_->height());
    
    float u0 = static_cast<float>(tex_x) / dbg_font_tex_width;
    float v0 = static_cast<float>(tex_y) / dbg_font_tex_height;
    
    float u1 = static_cast<float>(tex_x + font_size) / dbg_font_tex_width;
    float v1 = static_cast<float>(tex_y + font_size) / dbg_font_tex_height;
    
    
    float half_width = width_ / 2;
    float half_height = height_ / 2;
    
    float x0 = x / half_width;
    float x1 = (x + font_pixel_size) / half_width;
    float y0 = 1.0f - (y / half_height);
    float y1 = 1.0f - ((y + font_pixel_size) / half_height);
    x0 -= 1.0f;
    x1 -= 1.0f;
    
    
    uint8_t cr = (color & 0xFF000000) >> 24;
    uint8_t cg = (color & 0x00FF0000) >> 16;
    uint8_t cb = (color & 0x0000FF00) >> 8;
    uint8_t ca = (color & 0x000000FF) >> 0;


    // シェーダで描画
    int position_slot = font_shader_.getAttributeLocation("in_position");
    int uv_slot = font_shader_.getAttributeLocation("in_uv");
    
    
    
    float varray[] = {
        x0, y0,
        x0, y1,
        x1, y0,
        x1, y1
    };
    float vuv[] = {
        u0, v0,
        u0, v1,
        u1, v0,
        u1, v1
    };
    cross::RenderSystem::setEnableVertexAttribute(position_slot);
    cross::RenderSystem::setEnableVertexAttribute(uv_slot);

    cross::RenderSystem::setVertexAttributePointer(
        position_slot,
        2,
        cross::RenderSystem::FLOAT,
        false,
        0,
        varray
    );
    cross::RenderSystem::setVertexAttributePointer(
        uv_slot,
        2,
        cross::RenderSystem::FLOAT,
        false,
        0,
        vuv
    );

    font_shader_.setAttribute(
        "in_color",
        (float)cr / 255.0f,
        (float)cg / 255.0f,
        (float)cb / 255.0f,
        (float)ca / 255.0f
    );
    cross::RenderSystem::drawArray(cross::RenderSystem::DrawMode::MODE_TRIANGLE_STRIP, 0, 4);

}

namespace t3 {


void initializeDebugPrint()
{

    //  フォント作成
    debugfont_ = TextureFactory::createFromData(
        "debugfont",
        dbg_font_.width_,
        dbg_font_.height_,
        cross::RenderSystem::ColorFormat::RGBA,
        dbg_font_.pixel_data_
    );
    T3_NULL_ASSERT(debugfont_);
    
    font_shader_.build(font_vsh, font_fsh);
    
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
    
    t3::Director::printDisplay(
        x,
        y,
        Color::magenta().rgba32(),
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
    
    t3::Director::printDisplay(
        x,
        y,
        color.rgba32(),
        DEBUG_FONT_POINT,
        buf
    );
}
  
void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const int font_size,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[BUFFER_LENGTH];
    vsnprintf(buf, BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    t3::Director::printDisplay(
        x,
        y,
        color.rgba32(),
        font_size,
        buf
    );
}


}   // namespace t3

