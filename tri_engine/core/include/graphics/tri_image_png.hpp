/**
    @file tri_image_png.hpp
    png画像ファイル.
*/

#ifndef TRI_PNG_HPP_INCLUDED
#define TRI_PNG_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "../base/tri_types.hpp"
#include "kernel/io/tri_file.hpp"




TRI_CORE_NS_BEGIN


///
/// pngイメージ
struct PngImage {
    ///
    /// コンストラクタ
    explicit PngImage(String path);

    ///
    /// コンストラクタ
    explicit PngImage(const File& file);

    ///
    /// デストラクタ
    ~PngImage();

    uint32_t width_;        ///< 幅
    uint32_t height_;       ///< 高さ
    uint8_t* data_;         ///< データ
    int bit_depth_;         ///< ビット深度
    int color_type_;        ///< カラータイプ
    int interlace_type_;    ///< インターレース方式
    int size_;              ///< サイズ
};


TRI_CORE_NS_END

#endif // TRI_PNG_HPP_INCLUDED
