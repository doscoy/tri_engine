////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_circle.hpp
    円プリミティブ.
*/

#ifndef TRI_CIRCLE_HPP_INCLUDED
#define TRI_CIRCLE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/math/tri_vec2.hpp"

///
/// TriENGINEのトップレベルネームスペース
TRI_CORE_NS_BEGIN


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


TRI_CORE_NS_END


#endif  // TRI_CIRCLE_HPP_INCLUDED
