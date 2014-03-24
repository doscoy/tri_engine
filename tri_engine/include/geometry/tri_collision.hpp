#ifndef TRI_COLLISION_HPP_INCLUDED
#define TRI_COLLISION_HPP_INCLUDED


#include "math/tri_math_types.hpp"

namespace t3 {
inline namespace geometry {


bool isHitPointAABB(
    const Vec2& point,
    const Vec2& aabb_refttop,
    const Vec2& aabb_size
);



}   // namespace geometry
}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
