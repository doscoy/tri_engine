
#ifndef TRI_MATH_UTIL_HPP_INCLUDED
#define TRI_MATH_UTIL_HPP_INCLUDED

#include "tri_math_define.hpp"
#include "../tri_develop_base.hpp"
#include <cmath>


namespace t3 {
inline namespace util {

//  大きい値を取得
template <typename T>
inline const T judgeMaximum(
    const T a,
    const T b
){
    static_assert( sizeof(T) <= sizeof(int), "This size is not support." );

    return ( a >= b ? a : b );
}

//  小さい値を取得
template <typename T>
inline const T judgeMinimum(
    const T a,
    const T b
){
    static_assert( sizeof(T) <= sizeof(int), "This size is not support." );

	return ( a <= b ? a : b );
}

//  範囲丸め込み
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

//  下限丸め込み
template <class T>
inline const void clampMinimum(
    T& value,
    const T& l
){
    if ( value < l ){
        value = l;
    }
	
}

//  上限丸め込み
template <class T>
inline const void clampMaximum(
    T& value,
    const T& h
){
	if ( value > h ){
		value = h;
	}
	
}

//  範囲判定
template <class T>
bool inRange(
    const T& value,
    const T& low,
    const T& high
){
    if(low <= value && value <= high){
        
        return true;
    }
    
    return false;
}


//  絶対値取得
template <class T>
inline const T absolute( const T& val )
{
	return ( val < 0 ? -val : val );
}


//  デグリーからラジアンへ変換
constexpr inline float toRadian( float degree ){
    return degree * PI / 180.0f;
}

//  ラジアンからデグリーへ変換
constexpr inline float toDegree( float radian ){
    return radian / PI * 180.0f;
}

//  sin
inline float sinf( float radian ){
    return std::sin( radian );
}

//  cos
inline float cosf( float radian ){
    return std::cos( radian );
}    

//  acos
inline float acosf( float radian ){
    return std::acos( radian );
}

//  sqrt
inline float sqrtf( float value ){
    return std::sqrt( value );
}

//  atan2
inline float atan2f( float y, float x ){
    return std::atan2( y, x );
}

//  浮動小数０判定
inline bool isZeroFloat( float f ){
    if ( f > -EPSILON && f < EPSILON ){
        return true;
    }
    
    return false;
}

} // inline namespace util
} // namespace t3




#endif // TRI_MATH_UTIL_HPP_INCLUDED