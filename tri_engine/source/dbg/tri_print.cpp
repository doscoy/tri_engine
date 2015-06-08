//
//  tri_print.cpp
//  gl_1
//
//  Created by 可児 哲郎 on 12/01/14.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "dbg/tri_print.hpp"
#include "dbg/tri_debug_writer.hpp"
#include "base/tri_director.hpp"


namespace t3 {


void printDisplay(
    const float x,
    const float y,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[DebugWriter::BUFFER_LENGTH];
    vsnprintf(buf, DebugWriter::BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    t3::Director::printDisplay(
        x,
        y,
        color_sample::magenta().rgba32(),
        DEBUG_FONT_POINT,
        buf
    );
}

void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[DebugWriter::BUFFER_LENGTH];
    vsnprintf(buf, DebugWriter::BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    t3::Director::printDisplay(
        x,
        y,
        color.rgba32(),
        DEBUG_FONT_POINT,
        buf
    );
}
  
void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const int font_size,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[DebugWriter::BUFFER_LENGTH];
    vsnprintf(buf, DebugWriter::BUFFER_LENGTH, fmt, arg);
    va_end(arg);
    
    t3::Director::printDisplay(
        x,
        y,
        color.rgba32(),
        font_size,
        buf
    );
}









}   // namespace t3

