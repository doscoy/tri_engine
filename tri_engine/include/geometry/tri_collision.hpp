#ifndef TRI_COLLISION_HPP_INCLUDED
#define TRI_COLLISION_HPP_INCLUDED


#include "math/tri_math_types.hpp"
#include "tri_circle.hpp"



namespace t3 {
inline namespace geometry {


bool isHitPointAABB(
    const Vec2& point,
    const Vec2& aabb_refttop,
    const Vec2& aabb_size
);

bool isHitCircleCircle(
    const Circle& a,
    const Circle& b
);

bool isHitCirclePoint(
    const Circle& circle,
    const Vec2& point
);

}   // namespace geometry
}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
