#ifndef TRI_COLLISION_MANAGER_HPP_INCLUDED
#define TRI_COLLISION_MANAGER_HPP_INCLUDED

#include "util/tri_hash_string.hpp"
#include "tri_collider.hpp"
#include "tri_event.hpp"
#include <memory>
#include <list>
#include "math/tri_vec2.hpp"
#include "util/tri_singleton.hpp"



namespace t3 {
inline namespace geometry {


class CollisionManager
    : public Singleton<CollisionManager>
{
    friend class Singleton<CollisionManager>;

public:
    void addCollider(
        std::shared_ptr<Collider> collider,
        HashString target
    );

    void removeCollider(
        std::shared_ptr<Collider> collider
    );

    void collisionDetection();
    
private:
    void judgeColliderPairs(
        std::shared_ptr<Collider>& a,
        std::shared_ptr<Collider>& b
    );
    
private:
    std::list<std::shared_ptr<Collider>> colliders_;
};


}   // namespace geometory
}   // namespace t3


#endif  // TRI_COLLISION_MANAGER_HPP_INCLUDED
