//
//  tri_assert.mm
//  TriEngine
//
//  Created by 可児 哲郎 on 11/09/23.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include <cmath>
#include <iostream>
#include "tri_assert.hpp"
#include "tri_trace.hpp"


namespace t3 {


bool isInvalidFloat(const float f)
{
    //  浮動少数の無効値チェック
    if ( std::isnan(f) ){
        return true;
    }
    if ( std::isinf(f) ){
        return true;
    }
    
    //  正常な浮動少数
    return false;
}


bool panic(
    const char* const exp,
    const char* const filename,
    int line,
    const char* const funcname,
    const char* const fmt,
    ...
){
    va_list msg;
    
	char buf[256];    
	va_start( msg, fmt );
	vsnprintf(buf, 256, fmt, msg);
	va_end(msg);
    
    trace("Assertion %s\n", exp);
    trace(" msg :%s", buf);
    trace(" file:%s(%d)", filename, line);
    trace(" func:%s", funcname);
    abort();
//    while(1){;}
    return 1;
}


} // namespace t3