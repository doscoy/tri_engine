
#include "geometry/tri_collider.hpp"




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
