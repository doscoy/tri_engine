/**
    @file tri_debug_string_buffer.hpp
    デバッグ文字列バッファ.
*/

#ifndef TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED
#define TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"
#include "util/tri_uncopyable.hpp"
#include "tri_debug_writer.hpp"

namespace t3 {


///
/// デバッグ文字のコンテナのサイズ
constexpr int DEBUG_STRING_ITEM_STR_SIZE = 95;

///
/// デバッグ用文字
struct DebugStringItem {
    uint32_t color_;
    int16_t x_;
    int16_t y_;
    char str_[DEBUG_STRING_ITEM_STR_SIZE];
    char size_;
};

///
/// デバッグ文字バッファ
class DebugStringBuffer
    : private Uncopyable
{
public:
    ///
    /// コンストラクタ
    DebugStringBuffer();

    ///
    /// デストラクタ
    ~DebugStringBuffer();
    
    
public:
    ///
    /// デバッグ文字列追加
    void addString(
        const float x,          ///< 位置ｘ
        const float y,          ///< 位置ｙ
        const uint32_t color,   ///< 表示色
        const int size,         ///< フォントサイズ
        const char* const str   ///< 文字列
    );
    
    ///
    /// バッファクリア
    void clearBuffer();

    ///
    /// バッファを描画
    void drawStrings();
    
private:
    ///
    /// 文字列のコンテナ
    Array<DebugStringItem, 300> buffer_;

    ///
    /// 追加済みサイズ
    int size_;
    
    DebugWriter writer_;
};





}   // namespace t3




#endif // TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED