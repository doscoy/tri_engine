
#include "geometry/tri_collider.hpp"




namespace t3 {
inline namespace geometry {

Collider::Collider(
    const HashString& name
)
    : collider_id_()
    , collider_name_(name)
    , owner_(0)
{
        
}



}   // namespace geometry
}   // namespace t3
