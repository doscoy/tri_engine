/**
    @file tri_text_loader.hpp
    テキストローダー.
*/

#ifndef TRI_TEXT_LOADER_HPP_INCLUDED
#define TRI_TEXT_LOADER_HPP_INCLUDED

#include "core/base/tri_types.hpp"
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


///
/// テキストファイルを読み込んで返す
String loadText(
    const char* const path
);

TRI_CORE_NS_END

#endif  //  TRI_TEXT_LOADER_HPP_INCLUDE
