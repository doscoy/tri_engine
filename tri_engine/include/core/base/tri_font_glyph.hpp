////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_font_glyph.hpp
    フォントグリフ.
*/

#ifndef tri_engine_tri_glyph_hpp
#define tri_engine_tri_glyph_hpp

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_utf8.hpp"

TRI_CORE_NS_BEGIN
 
 

///
/// グリフ位置
struct GlyphPosition {
	int16_t x_;     ///< x
	int16_t y_;     ///< y
};

///
/// グリフメトリクス
struct GlyphMetrics {
	int8_t x_bearing_;  ///< xベアリング
	int8_t y_bearing_;  ///< yベアリング
	int8_t width_;      ///< 幅
	int8_t height_;     ///< 高さ
	int8_t x_advance_;  ///< 
	int8_t y_advance_;  ///< 
};

///
/// グリフ
struct Glyph {
	GlyphPosition position_;    ///< グリフ位置
	GlyphMetrics metrics_;      ///< メトリクス
	const char* char_;          ///< 文字
};

///
/// グリフ検索
inline const Glyph* searchGryph(
    const char* c,      ///< 文字
    const Glyph* list,  ///< グリフリスト
    size_t list_size    ///< リストサイズ
) {

    return nullptr;
}


///
/// グリフリスト
class GlyphList {
public:
    ///
    /// コンストラクタ
    GlyphList(const Glyph* list, int list_size, String font_sheet, int default_font_size)
        : list_(list)
        , list_size_(list_size)
        , font_sheet_name_(font_sheet)
        , default_font_size_(default_font_size)
    {
    
    }

    ///
    /// デストラクタ
    ~GlyphList() {
    
    }
    
public:
    ///
    /// グリフ検索
    const Glyph* search(const char* const c) const {
    
        for (int i = 0; i < list_size_; ++i) {
            const Glyph* glyph = &list_[i];
            
            if (isCompUTF8Char(glyph->char_, c)) {
                return glyph;
            }
        }
        return nullptr;
    }
    
    ///
    /// フォントシート名取得
    const String& fontSheetName() const {
        return font_sheet_name_;
    }
    
    ///
    /// デフォルトフォントサイズ取得
    int defaultFontSize() const {
        return default_font_size_;
    }

private:
    const Glyph* list_;         ///< グリフリスト
    int list_size_;             ///< リストサイズ
    String font_sheet_name_;    ///< フォントシート名
    int default_font_size_;     ///< デフォルトのフォントサイズ
};





TRI_CORE_NS_END


#endif
