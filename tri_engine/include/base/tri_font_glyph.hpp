//
//  tri_glyph.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/17.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_glyph_hpp
#define tri_engine_tri_glyph_hpp

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





inline bool isCompUTF8Char(
    const char* const a,
    const char* const b
) {

    for (int i = 0; i < 3; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }


    return true;
}


inline const Glyph* searchGryph(
    const char* c,
    const Glyph* list,
    size_t list_size
) {

    for (int i = 0; i < list_size; ++i) {
        const Glyph* glyph = &list[i];
        
        if (isCompUTF8Char(glyph->char_, c)) {
            return glyph;
        }
    }
    return nullptr;
}



}   // namespace t3


#endif
