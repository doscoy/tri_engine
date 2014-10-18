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
    enum class AlignX {
        LEFT,
        CENTER,
        RIGHT
    };
    
    enum class AlignY {
        TOP,
        CENTER,
        BOTTOM
    };

public:
    TextBox(SpriteLayer* layer, const GlyphList* glyph_list);
    ~TextBox();
    
public:
    TextBox& text(const Utf8& text);
    
    TextBox& center(const Vec2& pos) {
        transform_->position(pos);
        return *this;
    }
    
    const Vec2& center() const {
        return transform_->position();
    }
    
    TextBox& size(const Vec2& size) {
        size_ = size;
        return *this;
    }
    
    const Vec2& size() const {
        return size_;
    }
    
    TextBox& alignX(AlignX align) {
        align_x_ = align;
        return *this;
    }
    
    TextBox& alignY(AlignY align) {
        align_y_ = align;
        return *this;
    }
    
    TextBox& fontsize(int size) {
        font_size_ = size;
        return *this;
    }
    
    void setup() {
        adjustStringLayout();
    }
    
private:
    void adjustStringLayout();
    int textWidth() const;

    
private:
    SpriteLayer* layer_;
    Transform2DPtr transform_;
    Vec2 size_;
    const GlyphList* glyph_list_;
    const Glyph* unknown_char_glyph_;
    std::vector<SpritePtr> char_sprites_;
    std::vector<const Glyph*> char_glyphs_;
    AlignX align_x_;
    AlignY align_y_;
    int font_size_;
};


}   // namespace t3


#endif
