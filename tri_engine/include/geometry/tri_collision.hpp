#ifndef TRI_COLLISION_HPP_INCLUDED
#define TRI_COLLISION_HPP_INCLUDED

//  include
#include "math/tri_math_types.hpp"
#include "tri_circle.hpp"
#include "tri_rectangle.hpp"


namespace t3 {

///
/// “_‚Æ‹éŒ`‚Ì“–‚½‚è”»’è.
bool isHitPointRectangle(
    const Vec2& point,
    const Rectangle& rect
);

///
/// ‰~‚Æ‰~‚Ì“–‚½‚è”»’è.
bool isHitCircleCircle(
    const Circle& a,
    const Circle& b
);

///
/// ‰~‚Æ“_‚Ì“–‚½‚è”»’è.
bool isHitCirclePoint(
    const Circle& circle,
    const Vec2& point
);

}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
