////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_collision_events.hpp
    衝突判定イベント定義.
*/

#ifndef TRI_COLLISION_EVENTS_HPP_INCLUDED
#define TRI_COLLISION_EVENTS_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/base/tri_event.hpp"
#include "core/math/tri_vec2.hpp"
#include "core/utility/tri_unique_id.hpp"
#include "tri_collider.hpp"

TRI_CORE_NS_BEGIN
TRI_EVENT_NS_BEGIN


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


    CollisionPair collision_pair_;  ///< ペア
};

///
/// コリジョンイベント
class CollisionTriggerEvent
    : public CollisionEvent {
public:
    ///
    /// イベントタイプ
    static const EventType TYPE;

    ///
    /// イベントタイプ取得
    const EventType& eventType() const override {
        return TYPE;
    }
};


///
/// コリジョンイベント
class CollisionLeaveEvent
    : public CollisionEvent {
public:
    ///
    /// イベントタイプ
    static const EventType TYPE;

    ///
    /// イベントタイプ取得
    const EventType& eventType() const override {
        return TYPE;
    }
};




TRI_EVENT_NS_END
TRI_CORE_NS_END

#endif  // TRI_COLLISION_EVENTS_HPP_INCLUDED
