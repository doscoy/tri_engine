

#include "geometry/tri_collision.hpp"



namespace t3 {
inline namespace geometry {

bool isHitPointAABB(
    const Vec2& point,
    const Vec2& aabb_refttop,
    const Vec2& aabb_size
) {
    Vec2 aabb_rightdown = aabb_refttop + aabb_size;
    if (point.x_ < aabb_refttop.x_ || point.x_ > aabb_rightdown.x_) {
        return false;
    }
    else if (point.y_ < aabb_refttop.y_ || point.y_ > aabb_rightdown.y_) {
        return false;
    }
    
    return true;
}


}   // namespace geometry
}   // namespace t3


