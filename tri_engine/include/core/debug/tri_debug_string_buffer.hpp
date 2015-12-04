////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_debug_string_buffer.hpp
    デバッグ文字列バッファ.
*/

#ifndef TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED
#define TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "cross/cross_std.hpp"


TRI_CORE_NS_BEGIN



///
/// デバッグ文字のコンテナのサイズ
constexpr int DEBUG_STRING_ITEM_STR_SIZE = 95;

///
/// デバッグ用文字
struct DebugStringItem {
    uint32_t color_;
    int16_t x_;
    int16_t y_;
    char character_;
    char size_;
};

using DebugStringItemContainer = Vector<DebugStringItem>;

///
/// デバッグ文字バッファ
class DebugStringBuffer
    : protected DebugStringItemContainer
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
    using DebugStringItemContainer::clear;

    ///
    /// pop_back
    using DebugStringItemContainer::pop_back;

    ///
    /// back
    using DebugStringItemContainer::back;
    
    ///
    /// empty
    using DebugStringItemContainer::empty;
};



TRI_CORE_NS_END




#endif // TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED