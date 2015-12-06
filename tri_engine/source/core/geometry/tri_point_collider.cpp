////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/geometry/tri_point_collider.hpp"
#include "core/geometry/tri_collision.hpp"
#include "core/geometry/tri_circle_collider.hpp"



TRI_CORE_NS_BEGIN



const HashString PointCollider::TYPE("tri_PointCollider");

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
    if (col.position_ == position_) {
        return true;
    }
    
    return false;
}

const HashString& PointCollider::getCollisionType() const {
    return TYPE;
}


TRI_CORE_NS_END


