//
//  tri_utf8string.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/10/17.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_tri_utf8string_hpp
#define tri_engine_tri_utf8string_hpp


#include "base/tri_std.hpp"

namespace t3 {


class Utf8 {
public:
    Utf8(const char* const str);
    ~Utf8();


public:
    int length() const {
        return  size_;
    }
    
    char* at(int idx) {
        return char_pos_.at(idx);
    }


private:
    uint32_t size_;
    Vector<char*> char_pos_;
    String raw_;
};


}   // namespace t3



#endif
