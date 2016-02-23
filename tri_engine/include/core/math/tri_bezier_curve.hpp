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
	Position2D& ans,      ///< 結果
	const Position2D& p0, ///< 点１
	const Position2D& p1, ///< 点２
	const Position2D& p2, ///< 点３
	const float t   ///< 係数
);

///
///  2次ベジェ曲線計算
void calcBezierCurve2(
	Position3D& ans,      ///< 結果
	const Position3D& p0, ///< 点１
	const Position3D& p1, ///< 点２
	const Position3D& p2, ///< 点３
	const float t   ///< 係数
);

///
///  2次ベジェ曲線計算　配列版
void calcBezierCurve2(
	Position3D& ans,          ///< 結果
	const Position3D pa[3],   ///< 3点
	const float t       ///< 係数
);

TRI_CORE_NS_END

#endif // TRI_BEZIER_CURVE_HPP_INCLUDED


