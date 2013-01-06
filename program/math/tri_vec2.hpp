/*
 *  tri_vec2.hpp
 *  TriEngine
 *
 *  Created by 可児 哲郎 on 11/09/22.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef TRI_VEC2_HPP_INCLUDED
#define TRI_VEC2_HPP_INCLUDED

#include "../math/tri_math_util.hpp"
#include "tri_basetypes.hpp"
#include <iostream>


namespace t3 {

template <typename T>
struct Vec2 {
    
    //  データ
    T x;
    T y;
    
    //  コンストラクタ
    Vec2()
    {}
    
    Vec2( const T x, const T y )
        : x(x)
        , y(y)
    {}
    
    template<typename O>
    Vec2<T>( const Vec2<O>& rhs )
        : x( rhs.x )
        , y( rhs.y )
    {
    }

   
 
    ~Vec2(){}
    
    //  内積
    T dotProduct( const Vec2& rhs ){
        return x * rhs.x + y * rhs.y;
    }
    
    //  ブレンド
    Vec2& blend( 
        const float t,
        const Vec2& v
    ) {
        x = x * (1 - t) + v.x * t;
        y = y * (1 - t) + v.y * t;
        return *this;
    }
    
    //  正規化
    void normalize()
    {
        normalize( *this, *this );
    }
    
    //  正規化したベクトルを取得
    Vec2 getNormalized() const {
        Vec2 rhs = *this;
        rhs.normalize();
        return rhs;
    }
    
    //  長さの二乗
    T lengthSquare() const {
        return ( x*x + y*y );
    }
    
    //  長さ
    T length() const {
        return t3::sqrtf( lengthSquare() );
    }
    
    //  反転
    void reverse() {
        x = -x;
        y = -y;
    }
    
    //  x軸反転
    void reverseX() {
        x = -x;
    }
    
    //  y軸反転
    void reverseY() {
        y = -y;
    }
    
    //  反転ベクトル取得
    Vec2 getReversed() const {
        
        return ivec2_t( -x, -y );
    }
    
    //  pointer
    const T* pointer() const {
        return &x;
    }
    
    //  Vec2 = Vec2
    Vec2& operator =( const Vec2& rhs ){
        x = rhs.x;
        y = rhs.y;
        
        return *this;
    }

        
    //  vec2 + vec2
    Vec2 operator +( const Vec2& rhs ) const {
        return Vec2( x + rhs.x, y + rhs.y );
    }
    
    //  vec2 - Vec2
    Vec2 operator -( const Vec2& rhs ) const {
        return Vec2( x - rhs.x, y - rhs.y );
    }
    
    //  vec2 * Vec2
    Vec2 operator *( const Vec2& rhs ) const {
        return Vec2( x * rhs.x, y * rhs.y );
    }
     //  Vec2 / s
    Vec2 operator /( const float s ) const {
        float tmp = 1.0f / s;
        return Vec2( x * tmp, y * tmp );
    }
    
    //  Vec2 * s
    Vec2 operator *( const float s ) const {
        return Vec2( x * s, y * s );
    }
    
    
    //  Vec2 += Vec2
    void operator +=( const Vec2& rhs ) {
        x += rhs.x;
        y += rhs.y;
    }
    
    //  Vec2 -= Vec2
    void operator -=( const Vec2& rhs ) {
        x -= rhs.y;
        y -= rhs.y;
    }
    
    //  Vec2 /= s
    void operator /=( const float s ) {
        float tmp = 1.0f / s;
        x *= tmp;
        y *= tmp;
    }
    
    //  Vec2 *= s
    void operator *=( const float s ) {
        x *= s;
        y *= s;
    }

    
    
    //  +Vec2
    Vec2 operator +() const {
        return *this;
    }
 
    //  -Vec2
    Vec2 operator -() const {
        return Vec2( -x, -y );
    }
    
    //  cast
    operator T*() {
        return &x;
    }
    
    //  cast const
    operator const T*() const {
        return &x;
    }
    
    //  Vec2 == Vec2
    bool operator==(const Vec2& v) const {
        return x == v.x && y == v.y;
    }
    
    //  dump
    void dump() const {
        std::cout << "x:" << x << " y:" << y << std::endl;
    }

public:
    static T dotProduct(
        const Vec2& v1,
        const Vec2& v2
    ){
        return v1.x * v2.x + v1.y * v2.y;
    }
    
    static Vec2& normalize(
        Vec2& dst,
        const Vec2& src
    ){
        float s = 1.0f / src.length();
        dst.x *= s;
        dst.y *= s;
        return dst;
    }
    
    //  ベクトル同士の距離を算出
    static T distance(
        const Vec2& v1,
        const Vec2& v2
    ){
        return sqrtf( distanceSquare( v1, v2 ) );
    }
    
    //  ベクトル同士の距離の二乗を算出
    static T distanceSquare(
        const Vec2& v1,
        const Vec2& v2
    ){
        Vec2 tmp = v1 - v2;
        return ( tmp.lengthSquare() );
    }
    
    //  同じ方向を向いているベクトルか判定
    static bool isSameDirection(
        const Vec2& v1,
        const Vec2& v2,
        const T score = 0.1f
    ){
        T dotv = dot( v1, v2 );
        return dotv >= score;
    }

    //  ベクトル同士のブレンド
    static Vec2 getBlendVector(
        const float t,
        const Vec2& v1,
        const Vec2& v2
    ){
        return Vec2(
            v1.x * (1 - t) + v2.x * t,
            v1.y * (1 - t) + v2.y * t
        );
    }

    
    template <typename P>
    P* Write(P* pData)
    {
        Vec2* pVector = (Vec2*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    
    
};


//  typedef
typedef Vec2<bool>      bvec2_t;
typedef Vec2<float>     vec2_t;
typedef Vec2<int>       ivec2_t;
    

} // namespace t3

#endif // TRI_VEC2_HPP_INCLUDED