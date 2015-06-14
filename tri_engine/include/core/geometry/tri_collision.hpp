/**
    @file tri_collision.hpp
    衝突判定用関数群.
*/

#ifndef TRI_COLLISION_HPP_INCLUDED
#define TRI_COLLISION_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/math/tri_math_types.hpp"
#include "tri_circle.hpp"
#include "tri_rectangle.hpp"


TRI_CORE_NS_BEGIN


///
/// 点と矩形の当たり判定.
bool isHitPointRectangle(
    const Vec2& point,
    const Rectangle& rect
);

///
/// 円と円の当たり判定.
bool isHitCircleCircle(
    const Circle& a,
    const Circle& b
);

///
/// 円と点の当たり判定.
bool isHitCirclePoint(
    const Circle& circle,
    const Vec2& point
);

TRI_CORE_NS_END


#endif  // TRI_FRUSTUM_HPP_INCLUDED
