////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/geometry/tri_circle_collider.hpp"
#include "core/geometry/tri_point_collider.hpp"
#include "core/geometry/tri_collision.hpp"

TRI_CORE_NS_BEGIN




const HashString CircleCollider::TYPE("tri_CircleCollider");


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



