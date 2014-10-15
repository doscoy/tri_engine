

#include "util/tri_string_util.hpp"
#include "math/tri_math_util.hpp"
#include <cstring>


namespace t3 {
inline namespace util {



int utf8Length(const char* const str, int n) {

    int str_len = strnlen(str, 24);
    int str_count = 0;

    const uint8_t* p = reinterpret_cast<const uint8_t*>(str);
    int byte_count = 0;
    int byte_size = 0;
    while (p) {
        if (inRange(*p, 0x00, 0x7f)) {
            //  1byte
            byte_size = 1;
            
        } else if (inRange(*p, 0xc2, 0xdf)) {
            //  2byte
            byte_size = 2;
            
        } else if (inRange(*p, 0xe0, 0xef)) {
            //  3byte
            byte_size = 3;
        
        } else if (inRange(*p, 0xf0, 0xf7)) {
            //  4byte
            byte_size = 4;
        } else {
            // 5-6byteの文字は実際には無い
            return 0;
        }
        
        //  文字数カウント
        str_count += 1;
        
        //  バイト数カウント
        byte_count += byte_size;
        
        //  ポインタ進める
        p += byte_size;
        
        if (str_count > n || str_len <= byte_count) {
            break;
        }
    }


    return str_count;
}




}   // util
}   // t3



