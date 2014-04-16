
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
    colliders_.push_back(collider);
}

void CollisionManager::removeCollider(
    std::shared_ptr<Collider> collider
) {
    colliders_.remove(collider);
}


void CollisionManager::collisionDetection() {
    for (auto& body: colliders_) {
        body->setJudged(false);
    }
    for (auto& body: colliders_) {
        body->setJudged(true);
        for (auto& target: colliders_) {
            if (target->isJudged()) {
                continue;
            }
            judgeColliderPairs(body, target);
        }
    }
}

void CollisionManager::judgeColliderPairs(
    std::shared_ptr<Collider>& a,
    std::shared_ptr<Collider>& b
) {
    //  CircleCollider
    if (b->getType() == CircleCollider::TYPE) {
        CircleCollider* circle_coll = static_cast<CircleCollider*>(b.get());
        if (a->isHit(*circle_coll)) {
            //  当たった
            auto event = std::make_shared<CollisionEvent>();
            event->pos_ = circle_coll->getCircle().getPosition();
            event->collision_pair_ = std::make_pair(a->getColliderID(), b->getColliderID());
            t3::safeQueEvent(event);
        }
    }
    //  PointCollider
    else if (b->getType() == PointCollider::TYPE) {
        PointCollider* point_coll = static_cast<PointCollider*>(b.get());
        if (a->isHit(*point_coll)) {
            //  当たった
            auto event = std::make_shared<CollisionEvent>();
            event->pos_ = point_coll->getPosition();
            event->collision_pair_ = std::make_pair(a->getColliderID(), b->getColliderID());
            t3::safeQueEvent(event);
        }
    }
}

    
}   // namaespace geometry
}   // namespace t3






