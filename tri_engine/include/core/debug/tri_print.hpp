/**
    @file tri_print.hpp
    デバッグ用画面プリント.
*/
#ifndef TRI_PRINT_HPP_INCLUDED
#define TRI_PRINT_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../graphics/tri_color.hpp"

TRI_CORE_NS_BEGIN



///
/// 画面にデバッグ描画
void printDisplay(
    const float x,      ///< x
    const float y,      ///< y
    const char* fmt,    ///< フォーマット文字列
    ...
);

///
/// 画面にデバッグ描画
void printDisplay(
    const float x,      ///< x
    const float y,      ///< y
    const Color& color, ///< 色
    const char* fmt,    ///< フォーマット文字列
    ...
);

///
/// 画面にデバッグ描画
void printDisplay(
    const float x,      ///< x
    const float y,      ///< y
    const Color& color, ///< 色
    const int size,     ///< フォントサイズ
    const char* fmt,    ///< フォーマット文字列
    ...
);


///
/// デバッグフォントのサイズ
constexpr int DEBUG_FONT_POINT = 16;




TRI_CORE_NS_END






#if DEBUG
#define TRI_DEVELOPMENT_ENABLE_PRINT_DISP 1
#else
#define TRI_DEVELOPMENT_ENABLE_PRINT_DISP 0
#endif

#if TRI_DEVELOPMENT_ENABLE_PRINT_DISP
#define T3_PRINT_DISP(x,y,...)     ::t3::printDisplay(x,y,__VA_ARGS__)
#else
#define T3_PRINT_DISP(x,y,...)     (void)0
#endif //   TRI_DEVELOPMENT_ENABLE_PRINT_DISP


#endif // TRI_DBG_HPP_INCLUDED
