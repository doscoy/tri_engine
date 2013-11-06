#ifndef TRI_DRAW_PRIMITIVE_HPP_INCLUDED
#define TRI_DRAW_PRIMITIVE_HPP_INCLUDED

#include "../math/tri_math_types.hpp"
#include "../gfx/tri_color.hpp"


namespace t3 {

inline namespace geometry {

class Plane;

}   // namespace geometry



inline namespace dbg {



void drawPoint(
    const Vec2& pos,
    const Color& color
);

void drawLine(
    const Vec2& start,
    const Vec2& end,
    const Color& color
);

void drawLine(
    float start_x,
    float start_y,
    float end_x,
    float end_y,
    const Color& color
);

void drawRectangle(
     const Vec2& left_up,
     const Vec2& size,
     const Color& color
);



void drawPlane(
    const Vec3& center,
    const Vec3& normal,
    const Vec3& size,
    const Color& color
);

inline void drawPlane(
    const Plane& plane,
    const Vec3& size,
    const Color& color
);

}   // inline namespace dbg
}   // namespace t3





#endif // TRI_DRAW_PRIMITIVE_HPP_INCLUDED