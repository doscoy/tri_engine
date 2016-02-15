////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/debug/tri_debug_log_buffer.hpp"



TRI_CORE_NS_BEGIN


DebugLogBuffer::DebugLogBuffer()
    : buffer_()
{
}

DebugLogBuffer::~DebugLogBuffer()
{}

void DebugLogBuffer::addString(const char *const str) {
    if (buffer_.size() > 40) {
        buffer_.pop_front();
    }
    DebugLogItem item;
    strncpy(item.str_, str, DEBUG_LOG_STRING_LENGTH);
    buffer_.push_back(item);
}



TRI_CORE_NS_END

