
#ifndef TRI_COLLISION_EVENTS_HPP_INCLUDED
#define TRI_COLLISION_EVENTS_HPP_INCLUDED

#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"


namespace t3 {
inline namespace geometry {
        
class CollisionEvent
    : public EventBase {
public:
    static const EventType TYPE;
    const EventType& getEventType() const override {
        return TYPE;
    }
        
    Vec2 pos_;
    std::pair<uid_t, uid_t> collision_pair_;
        
};


}   // namespace geometry
}   // namespace t3

#endif  // TRI_COLLISION_EVENTS_HPP_INCLUDED
