#ifndef TRI_COLLISION_HPP_INCLUDED
#define TRI_COLLISION_HPP_INCLUDED


#include "math/tri_math_types.hpp"
#include "tri_circle.hpp"
#include "tri_rectangle.hpp"


namespace t3 {



bool isHitPointRectangle(
    const Vec2& point,
    const Rectangle& rect
);

bool isHitCircleCircle(
    const Circle& a,
    const Circle& b
);

bool isHitCirclePoint(
    const Circle& circle,
    const Vec2& point
);

}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
