
#ifndef TRI_PRINT_HPP_INCLUDED
#define TRI_PRINT_HPP_INCLUDED

#include "../gfx/tri_color.hpp"

namespace t3 {
inline namespace dbg {

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

} // inline namespace dbg
} // namespace t3

#endif // TRI_DBG_HPP_INCLUDED

