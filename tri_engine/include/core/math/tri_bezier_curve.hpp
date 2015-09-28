////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_bezier_curve.hpp
    ベジェ曲線.
*/

#ifndef TRI_BEZIER_CURVE_HPP_INCLUDED
#define TRI_BEZIER_CURVE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_math_types.hpp"


TRI_CORE_NS_BEGIN


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

TRI_CORE_NS_END

#endif // TRI_BEZIER_CURVE_HPP_INCLUDED


