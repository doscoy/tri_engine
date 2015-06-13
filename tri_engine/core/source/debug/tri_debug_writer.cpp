
#include "debug/tri_debug_writer.hpp"
#include "../shader/tri_font.fsh"
#include "../shader/tri_font.vsh"

// .cpp
#include "tri_debug_font_data.cpp"


TRI_CORE_NS_BEGIN





DebugWriter::DebugWriter()
    : width_()
    , height_()
    , font_sheet_()
    , shader_()
{
    font_sheet_ = Texture::create(
        String("debugfont"),
        dbg_font_.width_,
        dbg_font_.height_,
        cross::RenderSystem::ColorFormat::RGBA,
        cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
        (uint8_t*)dbg_font_.pixel_data_
    );

    shader_ = Shader::create(font_vsh, font_fsh);
}

DebugWriter::~DebugWriter() {

}











void DebugWriter::beginPrint(
    const float w,
    const float h
){
    width_ = w;
    height_ = h;

    cross::RenderSystem::resetBufferBind();
    font_sheet_->bind();

    //  シェーダ切り替え
    bool shader_setup_result = shader_->use();
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
    shader_->setUniform("sampler", 0);
   
}


void DebugWriter::endPrint()
{

    cross::RenderSystem::setBlend(false);
}


void DebugWriter::print(
    const char* str,
    const int x,
    const int y,
    const rgba32_t color,
    const int size
) {

    int font_size = size;
    int pitch = font_size - 2;
    int idx = 0;
    const char* c = str;
    while(*c){
        printCore( *c, x + idx * pitch, y, color, font_size );
        ++c;
        ++idx;
    }

}


void DebugWriter::printCore(
    const char c,
    const int x,
    const int y,
    const t3::rgba32_t color,
    const int font_pixel_size
){
    char char_idx = c - '!' + 1;


    constexpr int font_size = 16;
    int width_num = font_sheet_->width() / font_size;
    int tex_x = (char_idx % width_num) * font_size;
    int tex_y = (char_idx / width_num) * font_size;
    
    float dbg_font_tex_width = static_cast<float>(font_sheet_->width());
    float dbg_font_tex_height = static_cast<float>(font_sheet_->height());
    
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
    int position_slot = shader_->getAttributeLocation("in_position");
    int uv_slot = shader_->getAttributeLocation("in_uv");
    
    
    
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
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        0,
        varray
    );
    cross::RenderSystem::setVertexAttributePointer(
        uv_slot,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        0,
        vuv
    );

    shader_->setAttribute(
        "in_color",
        (float)cr / 255.0f,
        (float)cg / 255.0f,
        (float)cb / 255.0f,
        (float)ca / 255.0f
    );
    cross::RenderSystem::drawArray(
        cross::RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        0,
        4
    );

////
    float vuv2[] = {
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
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        0,
        varray
    );
    cross::RenderSystem::setVertexAttributePointer(
        uv_slot,
        2,
        cross::RenderSystem::TypeFormat::FLOAT,
        false,
        0,
        vuv2
    );

    shader_->setAttribute(
        "in_color",
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );
    cross::RenderSystem::drawArray(
        cross::RenderSystem::DrawMode::MODE_TRIANGLE_STRIP,
        0,
        4
    );


}


TRI_CORE_NS_END
