//
//  tri_gui_textbox.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/16.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_gui_textbox_hpp
#define tri_engine_tri_gui_textbox_hpp


#include "math/tri_vec2.hpp"
#include "gfx/tri_sprite_layer.hpp"
#include "base/tri_font_glyph.hpp"
#include "geometry/tri_transform.hpp"
#include "util/tri_utf8.hpp"

namespace t3 {


class TextBox {
public:
    TextBox(SpriteLayer* layer, const String font_seet);
    ~TextBox();
    
public:
    void setArea(const Vec2& center, const Vec2& size);
    void setText(const Utf8 text);

private:
    SpriteLayer* layer_;
    String font_seet_name_;
    Transform2DPtr transform_;
    Vec2 size_;
    Glyph* glyph_list_;
    
    std::vector<SpritePtr> char_list_;
};


}   // namespace t3


#endif
