#ifndef TRI_COLLISION_MANAGER_HPP_INCLUDED
#define TRI_COLLISION_MANAGER_HPP_INCLUDED

#include "util/tri_hash_string.hpp"
#include "tri_collision_events.hpp"
#include "tri_event.hpp"
#include <memory>
#include <list>
#include <vector>
#include <map>
#include "math/tri_vec2.hpp"
#include "util/tri_singleton.hpp"



namespace t3 {
inline namespace geometry {

using Colliders = std::list<std::shared_ptr<Collider>>;
using CollidersPtr = std::shared_ptr<Colliders>;



class CollisionManager
    : public Singleton<CollisionManager>
{
    friend class Singleton<CollisionManager>;

private:
    using JudgedPairs = std::vector<CollisionPair>;
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


}   // namespace geometory
}   // namespace t3


#endif  // TRI_COLLISION_MANAGER_HPP_INCLUDED
