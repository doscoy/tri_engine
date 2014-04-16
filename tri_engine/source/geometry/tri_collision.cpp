

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



bool isHitCircleCircle(
    const Circle& a,
    const Circle& b
) {
    Vec2 diff = a.getPosition() - b.getPosition();
    float distance_sq = (diff.x_ * diff.x_) + (diff.y_ * diff.y_);
    float radius_sum = a.getRadius() + b.getRadius();
    float radius_sq = radius_sum * radius_sum;
    
    if (distance_sq < radius_sq) {
        return true;
    }
    return false;
}

bool isHitCirclePoint(
    const Circle& circle,
    const Vec2& point
) {
    Vec2 diff = circle.getPosition() - point;
    float distance_sq = (diff.x_ * diff.x_) + (diff.y_ * diff.y_);
    float radius_sq = circle.getRadius() * circle.getRadius();

    if (distance_sq < radius_sq) {
        return true;
    }
    return false;
}



}   // namespace geometry
}   // namespace t3


