
#ifndef TRI_COLLISION_EVENTS_HPP_INCLUDED
#define TRI_COLLISION_EVENTS_HPP_INCLUDED

#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "util/tri_unique_id.hpp"
#include "tri_collider.hpp"

namespace t3 {
inline namespace geometry {
    
using CollisionPair = std::pair<ColliderPtr, ColliderPtr>;
    

class CollisionEvent
    : public EventBase {
public:
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }
        
    Vec2 pos_;
    CollisionPair collision_pair_;
};


}   // namespace geometry
}   // namespace t3

#endif  // TRI_COLLISION_EVENTS_HPP_INCLUDED
