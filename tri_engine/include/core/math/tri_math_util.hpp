////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_math_util.hpp
    算術系ユーティリティ.
*/

#ifndef TRI_MATH_UTIL_HPP_INCLUDED
#define TRI_MATH_UTIL_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_math_define.hpp"
#include <cmath>


TRI_CORE_NS_BEGIN


///
/// 大きい値を取得
template <typename T>
inline const T judgeMaximum(
    const T a,
    const T b
){
    static_assert( sizeof(T) <= sizeof(int), "This size is not support." );

    return ( a >= b ? a : b );
}

///
/// 小さい値を取得
template <typename T>
inline const T judgeMinimum(
    const T a,
    const T b
){
    static_assert( sizeof(T) <= sizeof(int), "This size is not support." );

	return ( a <= b ? a : b );
}

///
/// 範囲丸め込み
template <typename T, typename T2, typename T3>
inline const void clampLimitation(
    T& value,
    const T2& l,
    const T3& h
){
	if ( value > h ){
		value = h;
	}
	else if ( value < l ){
		value = l;
	}
}

///
/// 下限丸め込み
template <class T>
inline const void clampMinimum(
    T& value,
    const T& l
){
    if (value < l){
        value = l;
    }
	
}

///
/// 上限丸め込み
template <class T>
inline const void clampMaximum(
    T& value,
    const T& h
){
	if ( value > h ){
		value = h;
	}
	
}

///
/// 範囲判定
template <class T, class U>
bool inRange(
    const T& value,
    const U& low,
    const U& high
){
    if(low <= value && value <= high){
        
        return true;
    }
    
    return false;
}

///
/// 絶対値取得
template <class T>
inline const T absolute(const T& val)
{
	return (val < 0 ? -val : val);
}

///
/// デグリーからラジアンへ変換
constexpr inline float toRadian(float degree) {
    return degree * PI / 180.0f;
}

///
/// ラジアンからデグリーへ変換
constexpr inline float toDegree(float radian) {
    return radian / PI * 180.0f;
}

///
/// sin
inline float sin(float radian) {
    return std::sin(radian);
}

///
/// cos
inline float cos(float radian) {
    return std::cos(radian);
}    

///
/// acos
inline float acos(float radian) {
    return std::acos(radian);
}

///
/// sqrt
inline float sqrt(float value) {
    return std::sqrt(value);
}

///
/// atan2
inline float atan2(float y, float x) {
    return std::atan2(y, x);
}


///
/// x * x + y * y
inline float hypotenuseSquare(
    float x,
    float y
) {
    return x * x + y * y;
}

///
/// x * x + y * y + z * z
inline float hypotenuseSquare(
    float x,
    float y,
    float z
) {
    return x * x + y * y + z * z;
}


///
/// x * x + y * yの平方根
inline float hypotenuse(
    float x,
    float y
) {
    return sqrtf(hypotenuseSquare(x, y));
}

///
/// x * x + y * y + z * zの平方根
inline float hypotenuse(
    float x,
    float y,
    float z
) {
    return sqrtf(hypotenuseSquare(x, y, z));
}


///
/// 浮動小数判定
inline bool isEqualFloat(
    float val,
    float f
) {
    return inRange(val, f-EPSILON, f+EPSILON);
}

///
/// 浮動小数0判定
inline bool isZeroFloat(float f) {
    
    return isEqualFloat(f, 0.0f);
}

///
/// ガウス関数.
/// ガウシアンフィルタ用
inline float gauss(float x, float sigma2) {
    double coeff = 1.0 / (2.0 * PI * sigma2);
    double expon = -(x*x) / (2.0 * sigma2);
    return static_cast<float>((coeff * exp(expon)));
}


TRI_CORE_NS_END


#endif // TRI_MATH_UTIL_HPP_INCLUDED

