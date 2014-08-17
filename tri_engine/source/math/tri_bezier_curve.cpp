/**
 *
 * 2次ベジェ曲線
 *
 **/


#include "math/tri_bezier_curve.hpp"


namespace {


inline float calcBezier2Curve(
	const float p1,
	const float p2,
	const float p3,
	const float t
){
	const float u = 1.0f - t;
	return ( u * u * p1 + 2.0f * u * t * p2 + t * t * p3 );
}

} // unnamed namespace



namespace t3 {


void calcBezierCurve2(
	Vec2& ans,
	const Vec2& p0,
	const Vec2& p1,
	const Vec2& p2,
	const float t
){

	ans.x_ = calcBezier2Curve( p0.x_, p1.x_, p2.x_, t );
	ans.y_ = calcBezier2Curve( p0.y_, p1.y_, p2.y_, t );
}


void calcBezierCurve2(
	Vec3& ans,
	const Vec3& p0,
	const Vec3& p1,
	const Vec3& p2,
	const float t
){

	ans.x_ = calcBezier2Curve( p0.x_, p1.x_, p2.x_, t );
	ans.y_ = calcBezier2Curve( p0.y_, p1.y_, p2.y_, t );
	ans.z_ = calcBezier2Curve( p0.z_, p1.z_, p2.z_, t );

}



void calcBezierCurve2(
	Vec3& ans,
	const Vec3 pa[3],
	const float t
){
	
	calcBezierCurve2( ans, pa[0], pa[1], pa[2], t );
}


} // namespace t3

