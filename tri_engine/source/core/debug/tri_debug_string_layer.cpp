////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "core/debug/tri_debug_string_layer.hpp"
#include "../debug/tri_debug_font_data.cpp"


TRI_CORE_NS_BEGIN

DebugStringLayer::DebugStringLayer(
    const String& name,
    const LayerBase::Priority priority
)   : SpriteLayer(name, priority)
    , buffer_()
    , sprites_()
    , font_sheet_()
{


    //  デバッグ用フォントシート作成
    font_sheet_ = Texture::create(
        String("debugfont"),
        dbg_font_.width_,
        dbg_font_.height_,
        cross::RenderSystem::ColorFormat::LUMINANCE_ALPHA,
        cross::RenderSystem::TypeFormat::UNSIGNED_BYTE,
        (uint8_t*)dbg_font_.pixel_data_
    );
}

DebugStringLayer::~DebugStringLayer() {

}


void DebugStringLayer::updateLayer(
    DeltaTime delta_time
) {
    resetSprites();
    SpriteLayer::updateLayer(delta_time);
}




void DebugStringLayer::resetSprites() {

    sprites_.clear();

    //  今フレームで登録されたデバッグ文字を新たに登録
    while (!buffer_.empty()) {
        //  末尾の文字を取り出す
        auto& item = buffer_.back();
        buffer_.pop_back();

        //  スプライト生成
        auto font = createSprite(font_sheet_);
        sprites_.push_back(font);
        font->size(item.size_);
        
        font->color(item.color_);
        
        //  位置設定
        font->transform()->position(item.x_, item.y_);
        


        //  UV設定
        char char_idx = item.character_ - '!' + 1;
        constexpr int font_char_size = 8;
        int width_num = font_sheet_->width() / font_char_size;
        int tex_x = (char_idx % width_num) * font_char_size;
        int tex_y = (char_idx / width_num) * font_char_size;
    
        float dbg_font_tex_width = static_cast<float>(font_sheet_->width());
        float dbg_font_tex_height = static_cast<float>(font_sheet_->height());
    
        float u0 = static_cast<float>(tex_x) / dbg_font_tex_width;
        float v0 = static_cast<float>(tex_y) / dbg_font_tex_height;
    
        float u1 = static_cast<float>(tex_x + font_char_size) / dbg_font_tex_width;
        float v1 = static_cast<float>(tex_y + font_char_size) / dbg_font_tex_height;
    
        font->textureCoord(u0, v0, u1, v1);
    }
}



TRI_CORE_NS_END


