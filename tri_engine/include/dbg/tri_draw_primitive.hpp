#ifndef TRI_DRAW_PRIMITIVE_HPP_INCLUDED
#define TRI_DRAW_PRIMITIVE_HPP_INCLUDED

#include "../math/tri_math_types.hpp"
#include "../gfx/tri_color.hpp"


namespace t3 {



class Plane;
class Segment;




void initializeDrawPrimitive();


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

void drawRectangleMinSize(
     const Vec2& min,
     const Vec2& size,
     const Color& color
);

void drawRectangleCenterSize(
     const Vec2& center,
     const Vec2& size,
     const Color& color
);

void drawRectangleViewport(
    const Vec2& left_top,
    const Vec2& right_bottom,
    const Color& color
);


void drawPlane(
    const Vec3& center,
    const Vec3& normal,
    const Vec3& size,
    const Color& color
);




}   // namespace t3



#endif // TRI_DRAW_PRIMITIVE_HPP_INCLUDED