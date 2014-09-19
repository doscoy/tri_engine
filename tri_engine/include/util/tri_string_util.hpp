
#ifndef TRI_STRING_UTIL_HPP_INCLUDED
#define TRI_STRING_UTIL_HPP_INCLUDED


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



}   // namespace util
}   // namespace t3




#endif  // TRI_STRING_UTIL_HPP_INCLUDED

