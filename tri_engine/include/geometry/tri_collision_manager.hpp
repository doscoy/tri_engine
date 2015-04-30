#ifndef TRI_COLLISION_MANAGER_HPP_INCLUDED
#define TRI_COLLISION_MANAGER_HPP_INCLUDED

#include "util/tri_hash_string.hpp"
#include "geometry/tri_collision_events.hpp"
#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "util/tri_singleton.hpp"
#include "base/tri_std.hpp"


namespace t3 {


using Colliders = List<SharedPtr<Collider>>;
using CollidersPtr = SharedPtr<Colliders>;



class CollisionManager
    : public Singleton<CollisionManager>
{
    friend class Singleton<CollisionManager>;

private:
    using JudgedPairs = Vector<CollisionPair>;
public:
    void addCollider(
        ColliderPtr collider,
        HashString target
    );

    void removeCollider(
        ColliderPtr collider
    );

    void collisionDetection();

private:
    void judgeColliderPairs(
        ColliderPtr& a,
        ColliderPtr& b
    );
    
    bool isJudgedPair(
        const CollisionPair& pair
    );
    
private:
    using CollidersMap = std::map<HashString, CollidersPtr>;
    CollidersMap colliders_;
    CollidersMap same_target_group_;
    JudgedPairs judged_pairs_;
};



}   // namespace t3


#endif  // TRI_COLLISION_MANAGER_HPP_INCLUDED
