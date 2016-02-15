////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_math_types.hpp
    算術系型定義.
*/

#ifndef TRI_MATH_TYPES_HPP_INCLUDED
#define TRI_MATH_TYPES_HPP_INCLUDED

//  include
#include "tri_vec2.hpp"
#include "tri_vec3.hpp"
#include "tri_vec4.hpp"
#include "tri_matrix.hpp"

TRI_CORE_NS_BEGIN

///
/// 3次元座標
struct Position3D
    : public Vec3
{};

///
/// 2次元座標
struct Position2D
    : public Vec2
{};

///
/// 回転角
struct Rotation
    : public Vec3
{};



TRI_CORE_NS_END

#endif // TRI_MATH_TYPES_HPP_INCLUDED
