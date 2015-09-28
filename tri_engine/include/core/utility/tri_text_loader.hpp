////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
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
