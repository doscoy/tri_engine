
#ifndef TRI_COLLIDER_HPP_INCLUDED
#define TRI_COLLIDER_HPP_INCLUDED

//  include
#include "util/tri_hash_string.hpp"
#include "util/tri_unique_id.hpp"
#include "util/tri_any.hpp"
#include "base/tri_std.hpp"


namespace t3 {

//  前方宣言
class PointCollider;
class CircleCollider;

///
/// 当たり判定オブジェクト
class Collider {

public:
    ///
    /// コンストラクタ
    Collider(
        const HashString& name
    );

    ///
    /// デストラクタ
    virtual ~Collider(){};
    
public:
    ///
    /// 当たり判定
    virtual bool isHit(
        const PointCollider& col    ///< 点
    ) const {
        return false;
    }
    
    ///
    /// 当たり判定
    virtual bool isHit(
        const CircleCollider& col   ///< 円
    ) const {
        return false;
    }

    ///
    /// 当たり判定タイプ取得
    virtual const HashString& getCollisionType() const = 0;

public:
    ///
    /// コライダID取得
    const UniqueID& colliderID() const {
        return collider_id_;
    }
    
    ///
    /// コライダ名取得
    const HashString& colliderName() const {
        return collider_name_;
    }

    ///
    /// オーナー設定
    void owner(Any any) {
        owner_ = any;
    }
    
    ///
    /// オーナー取得
    Any& owner() {
        return owner_;
    }
    
    ///
    /// オーナー取得
    const Any& owner() const {
        return owner_;
    }


public:
    ///
    /// コライダ同士の判定
    bool operator ==(const Collider& rhs) {
        return colliderID() == rhs.colliderID();
    }

private:
    UniqueID collider_id_;      ///< コライダID
    HashString collider_name_;  ///< コライダ名
    Any owner_;                 ///< オーナー
};

///
/// コライダのポインタ
using ColliderPtr = SharedPtr<Collider>;

        

}   // namespace t3


#endif
