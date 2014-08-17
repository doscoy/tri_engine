//
//  tri_debug_log_buffer.cpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/11/01.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//


#include "dbg/tri_debug_log_buffer.hpp"
#include <cstdarg>
#include "dbg/tri_trace.hpp"

namespace t3 {
inline namespace dbg {


DebugLogBuffer::DebugLogBuffer()
    : buffer_()
{
}

DebugLogBuffer::~DebugLogBuffer()
{
}


void DebugLogBuffer::addString(
    const char* const str
) {
    if (buffer_.size() >= DEBUG_LOG_BUFFER_SIZE) {
        //  バッファの限界に達していたので古いデータを破棄
        buffer_.pop_front();
    }

    
    DebugLogItem new_item;
    std::strncpy(new_item.str_, str, DEBUG_LOG_STRING_LENGTH);
    
    buffer_.push_back(new_item);
    
    
}




}   // dbg
}   // t3