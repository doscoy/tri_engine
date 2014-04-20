
#include "geometry/tri_collision_manager.hpp"
#include "geometry/tri_circle_collider.hpp"
#include "geometry/tri_point_collider.hpp"
#include "base/tri_event_manager.hpp"
#include "geometry/tri_collision_events.hpp"




namespace t3 {
inline namespace geometry {


void CollisionManager::addCollider(
    std::shared_ptr<Collider> collider,
    t3::HashString target
) {

    //  共通の対象を持つグループに登録
    CollidersMap::iterator target_it = same_target_group_.find(target);

    if (target_it == same_target_group_.end()) {
        //  未登録のグループ
        CollidersMap::value_type new_item = std::make_pair(
            target,
            std::make_shared<Colliders>()
        );
        same_target_group_.insert(new_item);
    }
    same_target_group_.at(target)->push_back(collider);
    
    
    //  自分の属するグループに登録
    const t3::HashString& group_name = collider->getColliderName();
    CollidersMap::iterator group_it = colliders_.find(group_name);
    if (group_it == colliders_.end()) {
        //  未登録のグループ
        CollidersMap::value_type new_item = std::make_pair(
            group_name,
            std::make_shared<Colliders>()
        );
        colliders_.insert(new_item);
    }
    colliders_.at(group_name)->push_back(collider);
    
}

void CollisionManager::removeCollider(
    std::shared_ptr<Collider> collider
) {
    //  自分の属するグループから削除
    const t3::HashString& group_name = collider->getColliderName();
    auto group_it = colliders_.find(group_name);
    if (group_it != colliders_.end()) {
        //  あった
        group_it->second->remove(collider);
    }

    //  対象を持つグループ側に登録されている自分を探す
    for (auto g: same_target_group_) {
        g.second->remove(collider);
    }
}


void CollisionManager::collisionDetection() {
    // 開始前準備
    judged_pairs_.clear();
    
    for (auto g :same_target_group_) {
        auto key = g.first;
        
        //  判定対象を探す
        auto it = colliders_.find(key);
        if (it == colliders_.end()) {
            //  対象となるコライダは登録されてません
            continue;
        }
        
        //  コライダの集合があった
        for (auto body: *g.second.get()) {
            for (auto target: *it->second.get()) {
                judgeColliderPairs(body, target);
            }
        }
    }
}

void CollisionManager::judgeColliderPairs(
    std::shared_ptr<Collider>& a,
    std::shared_ptr<Collider>& b
) {
    //  既に判定済の組み合わせは省く
    CollisionPair pair = CollisionPair(a->getColliderID(), b->getColliderID());
    if (isJudgedPair(pair)) {
        return;
    }

    //  CircleCollider
    if (b->getCollisionType() == CircleCollider::TYPE) {
        CircleCollider* circle_coll = static_cast<CircleCollider*>(b.get());
        if (a->isHit(*circle_coll)) {
            T3_TRACE("hit\n");
            //  当たった
            auto event = std::make_shared<CollisionEvent>();
            event->pos_ = circle_coll->getCircle().getPosition();
            event->collision_pair_ = std::make_pair(a->getColliderID(), b->getColliderID());
            t3::safeQueEvent(event);
        }
    }
    //  PointCollider
    else if (b->getCollisionType() == PointCollider::TYPE) {
        PointCollider* point_coll = static_cast<PointCollider*>(b.get());
        if (a->isHit(*point_coll)) {
            //  当たった
            auto event = std::make_shared<CollisionEvent>();
            event->pos_ = point_coll->getPosition();
            event->collision_pair_ = std::make_pair(a->getColliderID(), b->getColliderID());
            t3::safeQueEvent(event);
        }
    }

    //  判定済登録
    judged_pairs_.push_back(pair);

}


bool CollisionManager::isJudgedPair(
    const CollisionPair& pair
) {
    JudgedPairs::iterator it = std::find_if(
        judged_pairs_.begin(),
        judged_pairs_.end(),
        [&](const CollisionPair& target){
            auto f = pair.first;
            auto s = pair.second;
            if (f == target.first) {
                if (s == target.second) {
                    return true;
                }
            }
            else if (f == target.second) {
                if (s == target.first) {
                    return true;
                }
            }
            return false;
        }
    );
    if (it != judged_pairs_.end()) {
        return true;
    }
    
    return false;
}


    
}   // namaespace geometry
}   // namespace t3






