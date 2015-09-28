////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_string_util.hpp
    文字列ユーティリティ.
*/

#ifndef TRI_STRING_UTIL_HPP_INCLUDED
#define TRI_STRING_UTIL_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/debug/tri_trace.hpp"
#include <cctype>

TRI_CORE_NS_BEGIN


///
/// 小文字化
inline void strToLower(
    char* str,
    int strlen
) {
    int count = 0;
    while(*str && count < strlen) {
        *str = (char)std::tolower((int)*str);
        ++str;
        ++count;
    }
}

///
/// 文字列を比較
inline int stringCompare(
    const char* const str1,
    const char* const str2,
    int length
) {
    return strncmp(str1, str2, length);
}


TRI_CORE_NS_END




#endif  // TRI_STRING_UTIL_HPP_INCLUDED

