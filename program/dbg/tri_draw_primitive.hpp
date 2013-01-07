#ifndef TRI_DRAW_PRIMITIVE_HPP_INCLUDED
#define TRI_DRAW_PRIMITIVE_HPP_INCLUDED

#include "../math/tri_math_types.hpp"
#include "../gfx/tri_color.hpp"


namespace t3 {
inline namespace dbg {



void drawPoint(
    const vec2_t& pos,
    const color_t& color
);

void drawLine(
    const vec2_t& start,
    const vec2_t& end,
    const color_t& color
);

void drawLine(
    float start_x,
    float start_y,
    float end_x,
    float end_y,
    const color_t& color
);

void drawRectangle(
     const vec2_t& left_up,
     const vec2_t& size,
     const color_t& color
);



void drawPlane(
    const vec3_t& center,
    const vec3_t& normal,
    const vec3_t& size,
    const color_t& color
);

}   // inline namespace dbg
}   // namespace t3





#endif // TRI_DRAW_PRIMITIVE_HPP_INCLUDED