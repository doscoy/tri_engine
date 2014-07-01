/**
 *
 * ベジェ曲線
 *
 **/

#ifndef TRI_BEZIER_CURVE_HPP_INCLUDED
#define TRI_BEZIER_CURVE_HPP_INCLUDED


#include "../math/tri_math_types.hpp"


namespace t3 {


//  2次ベジェ曲線計算
void calcBezierCurve2(
	Vec2& ans,
	const Vec2& p0,
	const Vec2& p1,
	const Vec2& p2,
	const float t
);

//  2次ベジェ曲線計算
void calcBezierCurve2(
	Vec3& ans,
	const Vec3& p0,
	const Vec3& p1,
	const Vec3& p2,
	const float t
);


//  2次ベジェ曲線計算　配列版
void calcBezierCurve2(
	Vec3& ans,
	const Vec3 pa[3],
	const float t
);

} // namespace t3

#endif // TRI_BEZIER_CURVE_HPP_INCLUDED


