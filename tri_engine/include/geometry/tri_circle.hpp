
#ifndef TRI_CIRCLE_HPP_INCLUDED
#define TRI_CIRCLE_HPP_INCLUDED

//  include
#include "math/tri_vec2.hpp"

namespace t3 {


///
/// 円
class Circle {
public:
    ///
    /// コンストラクタ
    Circle()
        : Circle(Vec2(0.0f, 0.0f), 1.0f)
    {}

    ///
    /// コンストラクタ.
    /// 座標、半径指定
    Circle(
        const Vec2& pos,
        float radius
    )   : position_(pos)
        , radius_(radius)
    {}


public:
    ///
    /// 位置設定
    void position(
        const Vec2& pos ///< 位置
    ) {
        position_ = pos;
    }

    ///
    /// 位置取得
    const Vec2& position() const {
        return position_;
    }
    
    ///
    /// 半径設定
    void radius(
        const float radius  ///< 半径
    ) {
        radius_ = radius;
    }
    
    ///
    /// 半径取得
    float radius() const {
        return radius_;
    }


private:
    Vec2 position_; ///< 位置
    float radius_;  ///< 半径
};


}   // namespace t3


#endif  // TRI_CIRCLE_HPP_INCLUDED
