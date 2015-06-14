/**
    @file tri_draw_primitive.hpp
    プリミティブ描画.
*/

#ifndef TRI_DRAW_PRIMITIVE_HPP_INCLUDED
#define TRI_DRAW_PRIMITIVE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_math_types.hpp"
#include "../graphics/tri_color.hpp"


TRI_CORE_NS_BEGIN



//  前方宣言
class Plane;
class Segment;



///
/// プリミティブ描画の初期化
void initializeDrawPrimitive();

///
/// 点を描画
void drawPoint(
    const Vec3& pos,    ///< 座標
    const Color& color  ///< 色
);


///
/// 線分を描画
void drawSegment(
    const Segment& segment, ///< 線分
    const Color& color,     ///< 色
    const float width       ///< 幅
);

///
/// 3軸を描画
void drawAxis(
    const Vec3& pos     ///< 座標
);

///
/// 2D矩形を描画.
/// 最小値と幅を指定
void drawRectangleMinSize(
     const Vec2& min,   ///< 最小値
     const Vec2& size,  ///< 幅
     const Color& color ///< 色
);

///
/// 2D矩形を描画.
/// 中心点と幅を指定
void drawRectangleCenterSize(
     const Vec2& center,    ///< 中心点
     const Vec2& size,      ///< サイズ
     const Color& color     ///< 色
);

///
/// 2D矩形を描画.
/// 左上と右下を指定
void drawRectangleViewport(
    const Vec2& left_top,       ///< 左上
    const Vec2& right_bottom,   ///< 右下
    const Color& color          ///< 色
);


///
/// 平面を描画
void drawPlane(
    const Vec3& center, ///< 平面の中心
    const Vec3& normal, ///< 平面の法線
    const Vec3& size,   ///< 平面のサイズ
    const Color& color  ///< 色
);




TRI_CORE_NS_END



#endif // TRI_DRAW_PRIMITIVE_HPP_INCLUDED