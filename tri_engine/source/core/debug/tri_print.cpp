
#include "core/debug/tri_print.hpp"
#include "core/base/tri_director.hpp"


TRI_CORE_NS_BEGIN

  
void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const int font_size,
    const char* fmt, ...
){

    va_list arg;
    va_start(arg, fmt);
    
    char buf[256];
    vsnprintf(buf, 256, fmt, arg);
    va_end(arg);
    
    t3::Director::printDisplay(
        x,
        y,
        color.rgba32(),
        font_size,
        buf
    );
}

TRI_CORE_NS_END

