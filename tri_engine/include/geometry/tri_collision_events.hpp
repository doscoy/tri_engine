/**
    @file tri_collision_events.hpp
    衝突判定イベント定義.
*/

#ifndef TRI_COLLISION_EVENTS_HPP_INCLUDED
#define TRI_COLLISION_EVENTS_HPP_INCLUDED

//  include
#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "util/tri_unique_id.hpp"
#include "tri_collider.hpp"

namespace t3 {

///
/// コライダ同士のペア
using CollisionPair = std::pair<ColliderPtr, ColliderPtr>;
    
///
/// コリジョンイベント
class CollisionEvent
    : public EventBase {
public:
    ///
    /// イベントタイプ
    static const EventType TYPE;

    ///
    /// イベントタイプ取得
    const EventType& eventType() const override {
        return TYPE;
    }

    ///
    /// 対象のペアが指定のIDを含んでいるか判定
    bool hasID(const UniqueID& id) const {
        if (id == collision_pair_.first->colliderID()) {
            return true;
        } else if (id == collision_pair_.second->colliderID()) {
            return true;
        }
        
        return false;
    }

    ///
    /// 指定IDじゃない方のオーナーオブジェクトを取得
    template <typename T>
    T getOtherOwner(const UniqueID& id) const {
        Any* owner = nullptr;
        if (collision_pair_.first->colliderID() == id) {
            owner = &collision_pair_.second->owner();
        } else {
            owner = &collision_pair_.first->owner();
        }
        return any_cast<T>(*owner);
    }



    Vec2 pos_;  ///< 位置
    CollisionPair collision_pair_;  ///< ペア
};


}   // namespace t3

#endif  // TRI_COLLISION_EVENTS_HPP_INCLUDED
