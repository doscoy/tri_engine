/**
    @file tri_bezier_curve.hpp
    ベジェ曲線.
*/

#ifndef TRI_BEZIER_CURVE_HPP_INCLUDED
#define TRI_BEZIER_CURVE_HPP_INCLUDED

//  include
#include "../math/tri_math_types.hpp"


namespace t3 {

///
///  2次ベジェ曲線計算
void calcBezierCurve2(
	Vec2& ans,      ///< 結果
	const Vec2& p0, ///< 点１
	const Vec2& p1, ///< 点２
	const Vec2& p2, ///< 点３
	const float t   ///< 係数
);

///
///  2次ベジェ曲線計算
void calcBezierCurve2(
	Vec3& ans,      ///< 結果
	const Vec3& p0, ///< 点１
	const Vec3& p1, ///< 点２
	const Vec3& p2, ///< 点３
	const float t   ///< 係数
);

///
///  2次ベジェ曲線計算　配列版
void calcBezierCurve2(
	Vec3& ans,          ///< 結果
	const Vec3 pa[3],   ///< 3点
	const float t       ///< 係数
);

} // namespace t3

#endif // TRI_BEZIER_CURVE_HPP_INCLUDED


