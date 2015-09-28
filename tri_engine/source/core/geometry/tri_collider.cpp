////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/geometry/tri_collider.hpp"

TRI_CORE_NS_BEGIN



Collider::Collider(
    const HashString& name
)
    : collider_id_()
    , collider_name_(name)
    , owner_(0)
{
        
}


TRI_CORE_NS_END
