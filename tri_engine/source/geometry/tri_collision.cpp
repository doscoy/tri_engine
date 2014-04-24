

#include "geometry/tri_collision.hpp"



namespace t3 {
inline namespace geometry {

bool isHitPointRectangle(
    const Vec2& point,
    const Rectangle& rect
) {

    const Vec2& min = rect.getMin();
    const Vec2& max = rect.getMax();

    if (point.x_ < min.x_ || point.x_ > max.x_) {
        return false;
    }
    else if (point.y_ < min.y_ || point.y_ > max.y_) {
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


