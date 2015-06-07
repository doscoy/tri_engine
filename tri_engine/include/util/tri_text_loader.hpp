/**
    @file tri_text_loader.hpp
    テキストローダー.
*/

#ifndef TRI_TEXT_LOADER_HPP_INCLUDED
#define TRI_TEXT_LOADER_HPP_INCLUDED

#include "base/tri_types.hpp"


namespace t3 {

///
/// テキストファイルを読み込んで返す
String loadText(
    const char* const path
);

}   // namespace t3

#endif  //  TRI_TEXT_LOADER_HPP_INCLUDE
