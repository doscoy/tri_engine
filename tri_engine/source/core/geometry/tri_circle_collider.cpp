#include "core/geometry/tri_circle_collider.hpp"
#include "core/geometry/tri_point_collider.hpp"
#include "core/geometry/tri_collision.hpp"

TRI_CORE_NS_BEGIN




const HashString CircleCollider::TYPE("CircleCollider");


CircleCollider::CircleCollider(
    const HashString& name
)   : Collider(name)
{
}




bool CircleCollider::isHit(
    const CircleCollider &col
) const {
    return isHitCircleCircle(circle_, col.circle());
}


bool CircleCollider::isHit(
    const PointCollider& col
) const {
    return isHitCirclePoint(circle_, col.position());
}


const HashString& CircleCollider::getCollisionType() const {
    return TYPE;
}

TRI_CORE_NS_END



