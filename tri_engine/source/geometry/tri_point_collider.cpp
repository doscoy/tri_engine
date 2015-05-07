
#include "geometry/tri_point_collider.hpp"
#include "geometry/tri_collision.hpp"
#include "geometry/tri_circle_collider.hpp"



namespace t3 {


const HashString PointCollider::TYPE("PointCollider");

PointCollider::PointCollider(
    const HashString& name
)   : Collider(name)
{
}


bool PointCollider::isHit(
    const CircleCollider &col
) const {
    return isHitCirclePoint(col.circle(), position_);
}

bool PointCollider::isHit(
    const PointCollider &col
) const {
    return false;
}

const HashString& PointCollider::getCollisionType() const {
    return TYPE;
}


}   // namespace t3