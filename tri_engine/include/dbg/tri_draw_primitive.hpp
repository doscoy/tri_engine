#ifndef TRI_DRAW_PRIMITIVE_HPP_INCLUDED
#define TRI_DRAW_PRIMITIVE_HPP_INCLUDED

#include "../math/tri_math_types.hpp"
#include "../gfx/tri_color.hpp"


namespace t3 {

inline namespace geometry {

class Plane;
class Segment;


}   // namespace geometry



inline namespace dbg {


void drawPoint(
    const Vec3& pos,
    const Color& color
);


void drawSegment(
    const Segment& segment,
    const Color& color,
    const float width
);

void drawAxis(const Vec3& pos);

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




}   // inline namespace dbg
}   // namespace t3



#endif // TRI_DRAW_PRIMITIVE_HPP_INCLUDED