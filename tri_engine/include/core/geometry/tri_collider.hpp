////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_collider.hpp
    衝突判定オブジェクト.
*/

#ifndef TRI_COLLIDER_HPP_INCLUDED
#define TRI_COLLIDER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_hash_string.hpp"
#include "core/utility/tri_unique_id.hpp"
#include "core/utility/tri_any.hpp"


TRI_CORE_NS_BEGIN


//  前方宣言
class PointCollider;
class CircleCollider;

///
/// 衝突判定オブジェクト
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

        

TRI_CORE_NS_END


#endif
