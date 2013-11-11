



#include <cstdarg>
#include <cstdio>
#include "tri_trace.hpp"
#include "../kernel/tri_game_system.hpp"
#include "../util/tri_counter.hpp"
#include "tri_debug_log_layer.hpp"
#include "../math/tri_math.hpp"


namespace t3 {
inline namespace dbg {


namespace {

DebugLogLayer dbg_log_layer_;

}   // unname namespace


void initializeTrace()
{
    //  デバッグレイヤーを登録
    GameSystem& gs = GameSystem::getInstance();
    gs.attachLayer( dbg_log_layer_ );

}

void traceTerminal( const char* const format, ... )
{
    va_list msg;
    
	char buf[256];    
	va_start( msg, format );
	vsnprintf(buf, 256, format, msg);
	va_end(msg);

    std::printf("%s", buf);
}

void traceDisplay( const char* const format, ... )
{
    va_list msg;
    
	char buf[256];    
	va_start( msg, format );
	vsnprintf(buf, 256, format, msg);
	va_end(msg);

    dbg_log_layer_.writeString(buf);
}

void trace( const char* const format, ... )
{
    va_list msg;
    
	char buf[256];    
	va_start( msg, format );
	vsnprintf(buf, 256, format, msg);
	va_end(msg);
    
    traceTerminal("%s", buf);
    traceDisplay("%s", buf);
}

void traceValue(
    const char* const name,
    ::std::size_t value
) {
    trace("[%d] %s=%u\n", frame_counter_.now(), name, value);
}

void traceValue(
    const char* const name,
    int value
) {
    trace("[%d] %s=%d\n", frame_counter_.now(), name, value);
}

void traceValue(
    const char* const name,
    uint32_t value
) {
    trace("[%d] %s=%u\n", frame_counter_.now(), name, value);
}

void traceValue(
    const char* const name,
    long value
) {
    trace("[%d] %s=%ld\n", frame_counter_.now(), name, value);
}

void traceValue(
    const char* const name,
    float value
) {
    trace("[%d] %s=%f\n", frame_counter_.now(), name, value);
}
    
void traceValue(
    const char* const name,
    void* value
) {
    trace("[%d] %s=%p\n", frame_counter_.now(), name, value);
}
    
void traceValue(
    const char* const name,
    const char* value
) {
    trace("[%d] %s=%s\n", frame_counter_.now(), name, value);
}

void traceValue(
    const char* const name,
    const Vec2& value
) {
    trace("[%d] %s=x:%f y:%f\n", frame_counter_.now(), name, value.x_, value.y_);
}

void traceValue(
    const char* const name,
    const Vec3& value
) {
    trace(
        "[%d] %s=x:%f y:%f z:%f\n",
        frame_counter_.now(),
        name,
        value.x_,
        value.y_,
        value.z_
    );
}

void traceValue(
    const char* const name,
    const Vec4& value
) {
    trace(
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
    const char* const name,
    const Mtx4& value
) {
    trace("[%d] %s\n", frame_counter_.now(), name);
    trace(
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.x_.x_, value.x_.y_, value.x_.z_, value.x_.w_
    );
    trace(
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.y_.x_, value.y_.y_, value.y_.z_, value.y_.w_
    );
    trace(
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.z_.x_, value.z_.y_, value.z_.z_, value.z_.w_
    );
    trace(
        "   %05.4f %05.4f %05.4f %05.4f\n",
        value.w_.x_, value.w_.y_, value.w_.z_, value.w_.w_
    );
    
}


}   // inline namespace dbg
}   // namespace t3

