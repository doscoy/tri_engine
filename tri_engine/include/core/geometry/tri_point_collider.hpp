////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_point_collider.hpp
    点衝突判定オブジェクト.
*/
#ifndef TRI_POINT_COLLIDER_HPP_INCLUDED
#define TRI_POINT_COLLIDER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_collider.hpp"
#include "core/math/tri_vec2.hpp"

TRI_CORE_NS_BEGIN



class CircleCollider;
class PointCollider;
using PointColliderPtr = SharedPtr<PointCollider>;


///
/// 点のコライダ
class PointCollider final
    : public Collider {
    ///
    /// コンストラクタ
    PointCollider(const HashString& name);

public:
    
    ///
    /// デストラクタ
    ~PointCollider(){}
            
public:
    ///
    /// 当たり判定
    bool isHit(const CircleCollider& col) const override;
    
    ///
    /// 当たり判定
    bool isHit(const PointCollider& col) const override;
    
    ///
    /// コリジョンタイプ取得
    const HashString& getCollisionType() const override;
    
    ///
    /// コリジョンのタイプ
    static const HashString TYPE;

public:
    ///
    /// 座標を取得
    const Vec2& position() const {
        return position_;
    }
    
    ///
    /// 座標を設定
    void position(const Vec2& pos) {
        position_ = pos;
    }
    
    static PointColliderPtr create(String name) {
        PointColliderPtr c(T3_SYS_NEW PointCollider(HashString(name)));
        return c;
    }

private:
    ///
    /// 座標
    Vec2 position_;
};
        
        

TRI_CORE_NS_END

#endif  // TRI_POINT_COLLIDER_HPP_INCLUDED

