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

    int str_len = strnlen(str, 24);
    int str_count = 0;

    const uint8_t* p = reinterpret_cast<const uint8_t*>(str);
    int byte_count = 0;
    int byte_size = 0;
    while (p) {
        pos_list.push_back((char*)p);
        if (t3::inRange(*p, 0x00, 0x7f)) {
            //  1byte
            byte_size = 1;
            
        } else if (t3::inRange(*p, 0xc2, 0xdf)) {
            //  2byte
            byte_size = 2;
            
        } else if (t3::inRange(*p, 0xe0, 0xef)) {
            //  3byte
            byte_size = 3;
        
        } else if (t3::inRange(*p, 0xf0, 0xf7)) {
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
}   // unname namespace

namespace t3 {

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

