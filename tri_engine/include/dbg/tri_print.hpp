
#ifndef TRI_PRINT_HPP_INCLUDED
#define TRI_PRINT_HPP_INCLUDED

#include "../gfx/tri_color.hpp"

namespace t3 {


void initializeDebugPrint();

void printDisplay(
    const float x,
    const float y,
    const char* fmt,
    ...
);

void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const char* fmt,
    ...
);

void printDisplay(
    const float x,
    const float y,
    const Color& color,
    const int size,
    const char* fmt,
    ...
);



constexpr int DEBUG_FONT_POINT = 16;

} // namespace t3


#if DEBUG
#define TRI_DEVELOPMENT_ENABLE_PRINT_DISP 1
#else
#define TRI_DEVELOPMENT_ENABLE_PRINT_DISP 0
#endif

#if TRI_DEVELOPMENT_ENABLE_PRINT_DISP
#define T3_PRINT_DISP(x,y,c,...)     ::t3::printDisplay(x,y,c,__VA_ARGS__)
#else
#define T3_PRINT_DISP(x,y,c,...)     (void)0
#endif //   TRI_DEVELOPMENT_ENABLE_PRINT_DISP


#endif // TRI_DBG_HPP_INCLUDED

