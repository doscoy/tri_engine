
#include "geometry/tri_point_collider.hpp"
#include "tri_collision.hpp"
#include "tri_circle_collider.hpp"



namespace t3 {
inline namespace geometry {

const HashString PointCollider::TYPE("PointCollider");

PointCollider::PointCollider(
    const HashString& name
)   : Collider(name)
{
}


bool PointCollider::isHit(
    const CircleCollider &col
) const {
    return isHitCirclePoint(col.getCircle(), position_);
}

bool PointCollider::isHit(
    const PointCollider &col
) const {
    return false;
}

const HashString& PointCollider::getCollisionType() const {
    return TYPE;
}


}   // namespace geometry
}   // namespace t3