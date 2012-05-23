/**
 *
 * ベジェ曲線
 *
 **/

#ifndef TRI_BEZIER_CURVE_HPP_INCLUDED
#define TRI_BEZIER_CURVE_HPP_INCLUDED


#include "../math/tri_vector.hpp"


namespace t3 {


//  2次ベジェ曲線計算
vec3_t& calcBezierCurve2(
	vec3_t& ans,
	const vec3_t& p0,
	const vec3_t& p1,
	const vec3_t& p2,
	const float t
);


//  2次ベジェ曲線計算　配列版
vec3_t& calcBezierCurve2(
	vec3_t& ans,
	const vec3_t pa[3],
	const float t
);

} // namespace t3

#endif // TRI_BEZIER_CURVE_HPP_INCLUDED


