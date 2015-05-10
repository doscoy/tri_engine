#ifndef TRI_POINT_COLLIDER_HPP_INCLUDED
#define TRI_POINT_COLLIDER_HPP_INCLUDED

//  include
#include "tri_collider.hpp"
#include "math/tri_vec2.hpp"


namespace t3 {


class CircleCollider;

///
/// 点のコライダ
class PointCollider
    : public Collider {
public:
    ///
    /// コンストラクタ
    PointCollider(const HashString& name);
    
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

private:
    ///
    /// 座標
    Vec2 position_;
};
        
        

}   // namespace t3

#endif  // TRI_POINT_COLLIDER_HPP_INCLUDED

