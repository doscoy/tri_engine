////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include <cstdarg>
#include <cstdio>
#include "core/debug/tri_trace.hpp"
#include "core/base/tri_director.hpp"
#include "core/utility/tri_counter.hpp"
#include "core/math/tri_math.hpp"


TRI_CORE_NS_BEGIN


namespace {


int trace_channel_mask_ = T3_TRACE_CHANNEL_MASK_ALL;

constexpr int TRACE_BUFFER_SIZE = 2048;

}   // unname namespace

void setTraceMask(int mask) {
    trace_channel_mask_ = mask;
}

void traceTerminal(const char* const format, ...)
{
    va_list msg;
    
	char buf[TRACE_BUFFER_SIZE];    
	va_start( msg, format );
	vsnprintf(buf, TRACE_BUFFER_SIZE, format, msg);
	va_end(msg);

    cross::printConsole(buf);
}

void traceDisplay(const char* const format, ...)
{
    va_list msg;
    
	char buf[TRACE_BUFFER_SIZE];    
	va_start( msg, format );
	vsnprintf(buf, TRACE_BUFFER_SIZE, format, msg);
	va_end(msg);

    auto& director = Director::instance();
    director.logDisplay(buf); 
}

void trace( 
    int ch,
    const char* const format, ... 
) {

    if (!(trace_channel_mask_ & ch)) {

        return;
    }


    va_list msg;
    
	char buf[TRACE_BUFFER_SIZE];    
	va_start( msg, format );
	vsnprintf(buf, TRACE_BUFFER_SIZE, format, msg);
	va_end(msg);
    
    uint32_t count = frame_counter_.now();

    traceTerminal("[%u]%s", count, buf);

//    traceDisplay("[%u]%s", count, buf);
}

void traceValue(
    int ch,
    const char* const name,
    int value
) {
    trace(ch, "[%d] %s=%d\n", frame_counter_.now(), name, value);
}

void traceValue(
    int ch,
    const char* const name,
    ::std::uint32_t value
) {
    trace(ch, "[%d] %s=%u\n", frame_counter_.now(), name, value);
}

void traceValue(
    int ch,
    const char* const name,
    long value
) {
    trace(ch, "[%d] %s=%ld\n", frame_counter_.now(), name, value);
}

void traceValue(
    int ch,
    const char* const name,
    float value
) {
    trace(ch, "[%d] %s=%f\n", frame_counter_.now(), name, value);
}
    
void traceValue(
    int ch,
    const char* const name,
    void* value
) {
    trace(ch, "[%d] %s=%p\n", frame_counter_.now(), name, value);
}
    
void traceValue(
    int ch,
    const char* const name,
    const char* value
) {
    trace(ch, "[%d] %s=%s\n", frame_counter_.now(), name, value);
}

void traceValue(
    int ch,
    const char* const name,
    const Vec2& value
) {
    trace(ch, "[%d] %s=x:%f y:%f\n", frame_counter_.now(), name, value.x_, value.y_);
}

void traceValue(
    int ch,
    const char* const name,
    const Vec3& value
) {
    trace(
        ch, 
        "[%d] %s=x:%f y:%f z:%f\n",
        frame_counter_.now(),
        name,
        value.x_,
        value.y_,
        value.z_
    );
}

void traceValue(
    int ch,
    const char* const name,
    const Vec4& value
) {
    trace(
        ch, 
        "[%d] %s=x:%f y:%f z:%f w:%f\n",
        frame_counter_.now(),
        name,
        value.x_,
        value.y_,
        value.z_,
        value.w_
    );
}


void traceValue(
    int ch,
    const char* const name,
    const Mtx44& value
) {
    trace(ch, "[%d] %s\n", frame_counter_.now(), name);
    trace(
        ch, 
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.x_.x_, value.x_.y_, value.x_.z_, value.x_.w_
    );
    trace(
        ch, 
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.y_.x_, value.y_.y_, value.y_.z_, value.y_.w_
    );
    trace(
        ch, 
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.z_.x_, value.z_.y_, value.z_.z_, value.z_.w_
    );
    trace(
        ch, 
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.w_.x_, value.w_.y_, value.w_.z_, value.w_.w_
    );
    
}

TRI_CORE_NS_END

