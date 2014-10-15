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




namespace t3 {


class TextBox {
public:
    explicit TextBox(SpriteLayer* layer);
    ~TextBox();
    
public:
    void setArea(const Vec2& center, const Vec2& size);
    void setText(const char* const text);

private:
    SpriteLayer* layer_;
    Vec2 center_;
    Vec2 size_;
};


}   // namespace t3


#endif
