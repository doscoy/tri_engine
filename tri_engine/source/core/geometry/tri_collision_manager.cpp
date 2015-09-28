////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/geometry/tri_collision_manager.hpp"
#include "core/geometry/tri_circle_collider.hpp"
#include "core/geometry/tri_point_collider.hpp"
#include "core/base/tri_event_manager.hpp"



TRI_CORE_NS_BEGIN




void CollisionManager::addCollider(
    ColliderPtr collider,
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
    const t3::HashString& group_name = collider->colliderName();
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
    ColliderPtr collider
) {
    //  自分の属するグループから削除
    const t3::HashString& group_name = collider->colliderName();
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
    ColliderPtr& a,
    ColliderPtr& b
) {
    //  既に判定済の組み合わせは省く
    CollisionPair pair = CollisionPair(a, b);
    if (isJudgedPair(pair)) {
        return;
    }

    //  CircleCollider
    if (b->getCollisionType() == CircleCollider::TYPE) {
        CircleCollider* circle_coll = static_cast<CircleCollider*>(b.get());
        if (a->isHit(*circle_coll)) {
            //  当たった
            auto event = std::make_shared<CollisionEvent>();
            event->pos_ = circle_coll->circle().position();
            event->collision_pair_ = std::make_pair(a, b);
            t3::EventManager::queueEvent(event);
        }
    }
    //  PointCollider
    else if (b->getCollisionType() == PointCollider::TYPE) {
        PointCollider* point_coll = static_cast<PointCollider*>(b.get());
        if (a->isHit(*point_coll)) {
            //  当たった
            auto event = std::make_shared<CollisionEvent>();
            event->pos_ = point_coll->position();
            event->collision_pair_ = std::make_pair(a, b);
            t3::EventManager::queueEvent(event);
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
            auto f = pair.first->colliderID();
            auto s = pair.second->colliderID();
            if (f == target.first->colliderID()) {
                if (s == target.second->colliderID()) {
                    return true;
                }
            }
            else if (f == target.second->colliderID()) {
                if (s == target.first->colliderID()) {
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



TRI_CORE_NS_END

