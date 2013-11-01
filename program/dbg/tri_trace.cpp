



#include <cstdarg>
#include <cstdio>
#include "tri_trace.hpp"
#include "../kernel/tri_game_system.hpp"
#include "../util/tri_counter.hpp"
#include "tri_debug_log_layer.hpp"



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
    
    traceTerminal( "%s", buf );
    traceDisplay( "%s", buf );
}

void traceValue(
    const char* const name,
    int value
){
    trace( "[%d] %s=%d\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    uint32_t value
){
    trace( "[%d] %s=%u\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    long value
){
    trace( "[%d] %s=%ld\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    float value
){
    trace( "[%d] %s=%f\n", frame_counter_.now(), name, value );
}
    
void traceValue(
    const char* const name,
    void* value
){
    trace( "[%d] %s=%p\n", frame_counter_.now(), name, value );
}
    
void traceValue(
    const char* const name,
    const char* value
){
    printf( "[%d] %s=%s\n", frame_counter_.now(), name, value );
}

   

}   // inline namespace dbg
}   // namespace t3

