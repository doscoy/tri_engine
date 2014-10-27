//
//  tri_glyph.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/17.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_glyph_hpp
#define tri_engine_tri_glyph_hpp

#include "util/tri_utf8.hpp"

namespace t3 {
 
 

 
struct GlyphPosition {
	int16_t x_;
	int16_t y_;
};

struct GlyphMetrics {
	int8_t x_bearing_;
	int8_t y_bearing_;
	int8_t width_;
	int8_t height_;
	int8_t x_advance_;
	int8_t y_advance_;
};

struct Glyph {
	GlyphPosition position_;
	GlyphMetrics metrics_;
	const char* char_;
};


inline const Glyph* searchGryph(
    const char* c,
    const Glyph* list,
    size_t list_size
) {

    
    return nullptr;
}



class GlyphList {
public:
    GlyphList(const Glyph* list, int list_size, String font_sheet, int default_font_size)
        : list_(list)
        , list_size_(list_size)
        , font_sheet_name_(font_sheet)
        , default_font_size_(default_font_size)
    {
    
    }
    ~GlyphList() {
    
    }
    
public:
    const Glyph* search(const char* const c) const {
    
        for (int i = 0; i < list_size_; ++i) {
            const Glyph* glyph = &list_[i];
            
            if (isCompUTF8Char(glyph->char_, c)) {
                return glyph;
            }
        }
        return nullptr;
    }
    
    const String& fontSheetName() const {
        return font_sheet_name_;
    }
    
    int defaultFontSize() const {
        return default_font_size_;
    }

private:
    const Glyph* list_;
    int list_size_;
    String font_sheet_name_;
    int default_font_size_;
};





}   // namespace t3


#endif
