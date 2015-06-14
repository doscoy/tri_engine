

#include "core/geometry/tri_collision.hpp"



TRI_CORE_NS_BEGIN



bool isHitPointRectangle(
    const Vec2& point,
    const Rectangle& rect
) {

    const Vec2& min = rect.min();
    const Vec2& max = rect.max();

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
    Vec2 diff = a.position() - b.position();
    float distance_sq = (diff.x_ * diff.x_) + (diff.y_ * diff.y_);
    float radius_sum = a.radius() + b.radius();
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
    Vec2 diff = circle.position() - point;
    float distance_sq = (diff.x_ * diff.x_) + (diff.y_ * diff.y_);
    float radius_sq = circle.radius() * circle.radius();

    if (distance_sq < radius_sq) {
        return true;
    }
    return false;
}


TRI_CORE_NS_END


