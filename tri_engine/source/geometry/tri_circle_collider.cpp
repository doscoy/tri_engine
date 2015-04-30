#include "geometry/tri_circle_collider.hpp"
#include "geometry/tri_point_collider.hpp"
#include "geometry/tri_collision.hpp"

namespace t3 {



const HashString CircleCollider::TYPE("CircleCollider");


CircleCollider::CircleCollider(
    const HashString& name
)   : Collider(name)
{
}




bool CircleCollider::isHit(
    const CircleCollider &col
) const {
    return isHitCircleCircle(circle_, col.getCircle());
}


bool CircleCollider::isHit(
    const PointCollider& col
) const {
    return isHitCirclePoint(circle_, col.position());
}


const HashString& CircleCollider::getCollisionType() const {
    return TYPE;
}

}   // namespace t3



