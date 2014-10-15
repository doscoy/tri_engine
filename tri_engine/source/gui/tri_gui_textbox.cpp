//
//  tri_gui_textbox.cpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/16.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "gui/tri_gui_textbox.hpp"

namespace t3 {



TextBox::TextBox(SpriteLayer* layer)
    : layer_(layer)
    , center_()
    , size_(128, 128)
{

}

TextBox::~TextBox() {

}


void TextBox::setArea(
    const Vec2& center,
    const Vec2& size
) {

    center_ = center;
    size_ = size;
}

void TextBox::setText(
    const char* const text
) {
    T3_TRACE("text length = %d", utf8Length(text));
}







}   // namespace t3






