//
//  tri_gui_textbox.cpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/16.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "gui/tri_gui_textbox.hpp"

namespace t3 {



TextBox::TextBox(SpriteLayer* layer, String font_seet)
    : layer_(layer)
    , font_seet_name_(font_seet)
    , transform_(nullptr)
    , size_(128, 128)
    , glyph_list_(nullptr)
    , char_list_()
{
    transform_ = std::make_shared<Transform2D>();
}

TextBox::~TextBox() {

}


void TextBox::setArea(
    const Vec2& center,
    const Vec2& size
) {

    transform_->position(center);
    size_ = size;
}

void TextBox::setText(
    const Utf8 text
) {
    T3_ASSERT(glyph_list_);
    T3_ASSERT(layer_);
    
    int char_num = text.length();
    T3_TRACE("text length = %d", char_num);
    
    
    for (int i = 0; i <char_num; ++i) {
        auto spr = layer_->createSprite(font_seet_name_);
        const char* const c = text.at(i);
        char_list_.push_back(c);
    }
}







}   // namespace t3






