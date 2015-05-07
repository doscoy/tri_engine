#ifndef TRI_COLLISION_HPP_INCLUDED
#define TRI_COLLISION_HPP_INCLUDED

//  include
#include "math/tri_math_types.hpp"
#include "tri_circle.hpp"
#include "tri_rectangle.hpp"


namespace t3 {

///
/// �_�Ƌ�`�̓����蔻��.
bool isHitPointRectangle(
    const Vec2& point,
    const Rectangle& rect
);

///
/// �~�Ɖ~�̓����蔻��.
bool isHitCircleCircle(
    const Circle& a,
    const Circle& b
);

///
/// �~�Ɠ_�̓����蔻��.
bool isHitCirclePoint(
    const Circle& circle,
    const Vec2& point
);

}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
