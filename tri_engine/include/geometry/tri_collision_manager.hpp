#ifndef TRI_COLLISION_MANAGER_HPP_INCLUDED
#define TRI_COLLISION_MANAGER_HPP_INCLUDED

//  include
#include "util/tri_hash_string.hpp"
#include "geometry/tri_collision_events.hpp"
#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "util/tri_singleton.hpp"
#include "base/tri_std.hpp"


namespace t3 {

///
/// コライダ集合
using Colliders = List<SharedPtr<Collider>>;

///
/// コライダ集合のポインタ
using CollidersPtr = SharedPtr<Colliders>;


///
/// コリジョンマネージャ
class CollisionManager
    : public Singleton<CollisionManager>
{
    friend class Singleton<CollisionManager>;

private:
    ///
    /// 判定済みペア
    using JudgedPairs = Vector<CollisionPair>;
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
    
private:
    ///
    ///  コライダコンテナ
    using CollidersMap = std::map<HashString, CollidersPtr>;

    CollidersMap colliders_;            ///< 管理コライダ
    CollidersMap same_target_group_;    ///< 同じ当たり判定対象を持つグループ
    JudgedPairs judged_pairs_;          ///< 判定済みのペア
};



}   // namespace t3


#endif  // TRI_COLLISION_MANAGER_HPP_INCLUDED
