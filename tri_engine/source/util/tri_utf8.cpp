//
//  tri_utf8.cpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/17.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "util/tri_utf8.hpp"
#include "math/tri_math_util.hpp"


namespace {

int utf8Setup(
    const char* const str,
    int n,
    t3::Vector<char*>& pos_list
) {

    size_t str_len = strnlen(str, 128);
    int str_count = 0;

    const uint8_t* p = reinterpret_cast<const uint8_t*>(str);
    int byte_count = 0;
    int byte_size = 0;
    while (p) {
        pos_list.push_back((char*)p);
        byte_size = t3::utf8ByteSize((char*)p);
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
}   // unname namespace

namespace t3 {

bool isCompUTF8Char(
    const char* const a,
    const char* const b
) {
    int unicode_size = utf8ByteSize(a);
    
    
    for (int i = 0; i < unicode_size; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }


    return true;
}

int utf8ByteSize(const char* const a) {
    uint8_t code = *a;
    if (t3::inRange(code, 0x00, 0x7f)) {
        //  1byte
        return 1;
            
    } else if (t3::inRange(code, 0xc2, 0xdf)) {
        //  2byte
        return 2;
            
    } else if (t3::inRange(code, 0xe0, 0xef)) {
        //  3byte
        return 3;
        
    } else if (t3::inRange(code, 0xf0, 0xf7)) {
        //  4byte
        return  4;
    }
    
    return 5;
}



Utf8::Utf8(const char* const str)
    : size_(0)
    , char_pos_()
    , raw_(str)
{
    size_ = utf8Setup(raw_.c_str(), 127, char_pos_);
}

Utf8::~Utf8() {

}






}   // namespace t3

