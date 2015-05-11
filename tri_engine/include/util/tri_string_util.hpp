/**
    @file tri_string_util.hpp
    文字列ユーティリティ.
*/

#ifndef TRI_STRING_UTIL_HPP_INCLUDED
#define TRI_STRING_UTIL_HPP_INCLUDED

//  include
#include "dbg/tri_trace.hpp"
#include <cctype>

namespace t3 {

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





}   // namespace t3




#endif  // TRI_STRING_UTIL_HPP_INCLUDED

