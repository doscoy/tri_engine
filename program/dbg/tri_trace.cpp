



#include <stdarg.h>
#include <stdio.h>
#include "tri_trace.hpp"
#include "../kernel/tri_game_system.hpp"
#include "../util/tri_counter.hpp"



namespace t3 {
inline namespace dbg {

void trace( const char* const format, ... ){
    va_list msg;
    
	char buf[256];    
	va_start( msg, format );
	vsnprintf(buf, 256, format, msg);
	va_end(msg);
    
    printf( "[%d] %s", frame_counter_.now(), buf );
}

void traceValue(
    const char* const name,
    int value
){
    printf( "[%d] %s=%d\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    u_int value
){
    printf( "[%d] %s=%d\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    long value
){
    printf( "[%d] %s=%ld\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    u_long value
){
    printf( "[%d] %s=%ld\n", frame_counter_.now(), name, value );
}

void traceValue(
    const char* const name,
    float value
){
    printf( "[%d] %s=%f\n", frame_counter_.now(), name, value );
}
    
void traceValue(
    const char* const name,
    void* value
){
    printf( "[%d] %s=%p\n", frame_counter_.now(), name, value );
}
    
void traceValue(
    const char* const name,
    const char* value
){
    printf( "[%d] %s=%s\n", frame_counter_.now(), name, value );
}

   

}   // inline namespace dbg
}   // namespace t3

