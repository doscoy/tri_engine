//
//  tri_gui_textbox.cpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/16.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "gui/tri_gui_textbox.hpp"

namespace t3 {



TextBox::TextBox(SpriteLayer* layer, const GlyphList* glyph_list)
    : layer_(layer)
    , transform_(nullptr)
    , size_(128, 128)
    , glyph_list_(glyph_list)
    , unknown_char_glyph_(nullptr)
    , char_sprites_()
    , char_glyphs_()
    , align_x_(AlignX::LEFT)
    , align_y_(AlignY::TOP)
    , font_size_(16)
    , auto_resize_(false)
    , font_color_()
{
    transform_ = std::make_shared<Transform2D>();
    unknown_char_glyph_ = glyph_list->search(u8"■");
}

TextBox::~TextBox() {

}



TextBox& TextBox::text(
    const Utf8& text
) {
    T3_ASSERT(glyph_list_);
    T3_ASSERT(layer_);

    char_sprites_.clear();
    char_glyphs_.clear();
    
    int char_num = text.length();

    for (int i = 0; i <char_num; ++i) {
        auto spr = layer_->createSprite(glyph_list_->fontSheetName().c_str());
        //  一文字取得
        const char* const c = text.at(i);

        //  グリフを得る
        const Glyph* glyph = glyph_list_->search(c);
        T3_NULL_ASSERT(glyph);
        if (!glyph) {
            continue;
        }
        
        if (!glyph) {
            glyph = unknown_char_glyph_;
        }
    
        t3::Vec2 left_top(
            glyph->position_.x_,
            glyph->position_.y_
        );
        t3::Vec2 size(
            glyph->metrics_.width_ + 1,
            glyph->metrics_.height_
        );
        spr->setupTextureCoordAndSize(left_top, size);
        spr->transform()->setParentTransform(transform_);


        char_sprites_.push_back(spr);
        char_glyphs_.push_back(glyph);
    }
    return *this;
}


void TextBox::adjustStringLayout() {
    int sprite_size = static_cast<int>(char_sprites_.size());
    int x_start = 0;
    int y_start = 0;
    
    int text_width = textWidth();
    //  横軸アライン設定
    if (align_x_ == AlignX::LEFT) {
        //  左寄せ
        x_start = -(size_.x_ / 2);
    } else if (align_x_ == AlignX::CENTER) {
        //  中央寄せ
        x_start = -(text_width / 2);
    } else {
        //  右寄せ
        x_start = (size_.x_ / 2) - text_width;
    }

    //  縦軸アライン設定
    if (align_y_ == AlignY::TOP) {
        //  上寄せ
        y_start = (size_.y_ / 2) - font_size_;
    } else if (align_y_ == AlignY::CENTER) {
        //  中央寄せ
        y_start = -(font_size_ / 3);
    } else {
        //  下寄せ
        y_start = -(size_.y_ / 2);
    }

    int x = x_start;
    int y = y_start;
    for (int i = 0; i < sprite_size; ++i) {
        //  文字のスプライトとグリフを取得
        auto& spr = char_sprites_[i];
        auto& glyph = char_glyphs_[i];
    
        float scale_ratio = fontScaleRatio();
        float width = glyph->metrics_.width_ * scale_ratio;
        float height = glyph->metrics_.height_ * scale_ratio;
        float x_bearing = glyph->metrics_.x_bearing_ * scale_ratio;
        float y_bearing = glyph->metrics_.y_bearing_ * scale_ratio;
        float x_advance = glyph->metrics_.x_advance_ * scale_ratio;

        Vec2 pen_pos(
            x + x_bearing + (width / 2),
            y - y_bearing - (height / 2)
        );
        spr->transform()->position(pen_pos);
        spr->transform()->scale(scale_ratio);
    
        x += x_advance;
    }
    
    if (auto_resize_) {
        //  はみ出ていたらフォントサイズを調整する
        while (size_.x_ < textWidth()) {
            if (font_size_ < 24) {
                //  24point以下になったらもう表示しちゃう
                T3_TRACE("[Worning] font size under 24.\n");
                break;
            }
            
            font_size_ -= 4;
            adjustStringLayout();
        }
    }
    
}


int TextBox::textWidth() const {

    int total_width = 0;
    for (auto glyph : char_glyphs_) {
        total_width += glyph->metrics_.x_advance_;
    }

    return total_width * fontScaleRatio();
}

float TextBox::fontScaleRatio() const {
    return (float)font_size_ / (float)glyph_list_->defaultFontSize();
}


void TextBox::updateColor() {
    for (auto& spr : char_sprites_) {
        spr->color(font_color_);
    }
}

}   // namespace t3






