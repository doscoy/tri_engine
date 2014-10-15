
#ifndef TRI_STRING_UTIL_HPP_INCLUDED
#define TRI_STRING_UTIL_HPP_INCLUDED

#include "dbg/tri_trace.hpp"
#include <cctype>

namespace t3 {
inline namespace util {


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


inline int stringCompare(
    const char* const str1,
    const char* const str2,
    int length
) {
    return strncmp(str1, str2, length);
}


int utf8Length(const char* const str, int n = 128);





}   // namespace util
}   // namespace t3




#endif  // TRI_STRING_UTIL_HPP_INCLUDED

