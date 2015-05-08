
#ifndef TRI_PNG_HPP_INCLUDED
#define TRI_PNG_HPP_INCLUDED

//  include
#include "../base/tri_types.hpp"
#include "kernel/io/tri_file.hpp"




namespace t3 {

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


}   // namespace t3

#endif // TRI_PNG_HPP_INCLUDED
