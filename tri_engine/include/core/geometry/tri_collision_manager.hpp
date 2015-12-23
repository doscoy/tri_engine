////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_collision_manager.hpp
    アーカイブ管理.
*/

#ifndef TRI_COLLISION_MANAGER_HPP_INCLUDED
#define TRI_COLLISION_MANAGER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_hash_string.hpp"
#include "core/geometry/tri_collision_events.hpp"
#include "core/base/tri_event.hpp"
#include "core/math/tri_vec2.hpp"
#include "core/utility/tri_singleton.hpp"

TRI_CORE_NS_BEGIN


///
/// コライダ集合
using Colliders = List<SharedPtr<Collider>>;

///
/// コライダ集合のポインタ
using CollidersPtr = SharedPtr<Colliders>;


///
/// コリジョンマネージャ
class CollisionManager final
    : public Singleton<CollisionManager>
{
    friend class Singleton<CollisionManager>;

private:
    ///
    /// 判定済みペア
    using ColliderPairs = Set<CollisionPair>;
    CollisionManager();
public:

    ///
    /// コライダ追加
    void addCollider(
        ColliderPtr collider,   ///< コライダ
        HashString target       ///< 対象の名前
    );

    ///
    /// コライダ削除
    void removeCollider(
        ColliderPtr collider    ///< コライダ
    );

    ///
    /// 総当たり判定
    void collisionDetection();

private:
    ///
    /// ペアの当たり判定
    void judgeColliderPairs(
        ColliderPtr& a,
        ColliderPtr& b
    );
    
    ///
    /// 判定済みペアか
    bool isJudgedPair(
        const CollisionPair& pair
    );
    
    ///
    /// カレントフレームでのヒットグループに登録
    void addCurrentCollidedPair(CollisionPair pair);
    
    ///
    /// 衝突中のペアのイベントを発行
    void queueCollisionEvent(ColliderPairs& pairs);
    
    void queueCollisionTriggerEvent(ColliderPairs& pairs);
    
    void queueCollisionLeaveEvent(ColliderPairs& pairs);
    
private:
    ///
    ///  コライダコンテナ
    using CollidersMap = std::map<HashString, CollidersPtr>;

    CollidersMap colliders_;            ///< 管理コライダ
    CollidersMap same_target_group_;    ///< 同じ当たり判定対象を持つグループ
    ColliderPairs judged_pairs_;        ///< 判定済みのペア
    ColliderPairs collided_[2];
    int current_collided_idx_;
    int last_collider_idx_;
};


TRI_CORE_NS_END

#endif  // TRI_COLLISION_MANAGER_HPP_INCLUDED
