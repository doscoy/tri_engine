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
#include <iostream>


namespace t3 {

template <typename T>
struct Vec2Template {
    
    //  データ
    T x;
    T y;
    
    //  コンストラクタ
    Vec2Template()
    {}
    
    Vec2Template( const T x, const T y )
        : x(x)
        , y(y)
    {}
    
    template<typename O>
    Vec2Template<T>( const Vec2Template<O>& rhs )
        : x( rhs.x )
        , y( rhs.y )
    {
    }

   
 
    ~Vec2Template(){}
    
    //  内積
    T dotProduct( const Vec2Template& rhs ){
        return x * rhs.x + y * rhs.y;
    }
    
    //  ブレンド
    Vec2Template& blend( 
        const float t,
        const Vec2Template& v
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
    Vec2Template getNormalized() const {
        Vec2Template rhs = *this;
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
    Vec2Template getReversed() const {
        
        return Point2( -x, -y );
    }
    
    //  pointer
    const T* pointer() const {
        return &x;
    }
    
    //  Vec2Template = Vec2Template
    Vec2Template& operator =( const Vec2Template& rhs ){
        x = rhs.x;
        y = rhs.y;
        
        return *this;
    }

        
    //  vec2 + vec2
    Vec2Template operator +( const Vec2Template& rhs ) const {
        return Vec2Template( x + rhs.x, y + rhs.y );
    }
    
    //  vec2 - Vec2Template
    Vec2Template operator -( const Vec2Template& rhs ) const {
        return Vec2Template( x - rhs.x, y - rhs.y );
    }
    
    //  vec2 * Vec2Template
    Vec2Template operator *( const Vec2Template& rhs ) const {
        return Vec2Template( x * rhs.x, y * rhs.y );
    }
     //  Vec2Template / s
    Vec2Template operator /( const float s ) const {
        float tmp = 1.0f / s;
        return Vec2Template( x * tmp, y * tmp );
    }
    
    //  Vec2Template * s
    Vec2Template operator *( const float s ) const {
        return Vec2Template( x * s, y * s );
    }
    
    
    //  Vec2Template += Vec2Template
    void operator +=( const Vec2Template& rhs ) {
        x += rhs.x;
        y += rhs.y;
    }
    
    //  Vec2Template -= Vec2Template
    void operator -=( const Vec2Template& rhs ) {
        x -= rhs.y;
        y -= rhs.y;
    }
    
    //  Vec2Template /= s
    void operator /=( const float s ) {
        float tmp = 1.0f / s;
        x *= tmp;
        y *= tmp;
    }
    
    //  Vec2Template *= s
    void operator *=( const float s ) {
        x *= s;
        y *= s;
    }

    
    
    //  +Vec2Template
    Vec2Template operator +() const {
        return *this;
    }
 
    //  -Vec2Template
    Vec2Template operator -() const {
        return Vec2Template( -x, -y );
    }
    
    //  cast
    operator T*() {
        return &x;
    }
    
    //  cast const
    operator const T*() const {
        return &x;
    }
    
    //  Vec2Template == Vec2Template
    bool operator==(const Vec2Template& v) const {
        return x == v.x && y == v.y;
    }
    
    //  dump
    void dump() const {
        std::cout << "x:" << x << " y:" << y << std::endl;
    }

public:
    static T dotProduct(
        const Vec2Template& v1,
        const Vec2Template& v2
    ){
        return v1.x * v2.x + v1.y * v2.y;
    }
    
    static Vec2Template& normalize(
        Vec2Template& dst,
        const Vec2Template& src
    ){
        float s = 1.0f / src.length();
        dst.x *= s;
        dst.y *= s;
        return dst;
    }
    
    //  ベクトル同士の距離を算出
    static T distance(
        const Vec2Template& v1,
        const Vec2Template& v2
    ){
        return sqrtf( distanceSquare( v1, v2 ) );
    }
    
    //  ベクトル同士の距離の二乗を算出
    static T distanceSquare(
        const Vec2Template& v1,
        const Vec2Template& v2
    ){
        Vec2Template tmp = v1 - v2;
        return ( tmp.lengthSquare() );
    }
    
    //  同じ方向を向いているベクトルか判定
    static bool isSameDirection(
        const Vec2Template& v1,
        const Vec2Template& v2,
        const T score = 0.1f
    ){
        T dotv = dot( v1, v2 );
        return dotv >= score;
    }

    //  ベクトル同士のブレンド
    static Vec2Template getBlendVector(
        const float t,
        const Vec2Template& v1,
        const Vec2Template& v2
    ){
        return Vec2Template(
            v1.x * (1 - t) + v2.x * t,
            v1.y * (1 - t) + v2.y * t
        );
    }

    
    template <typename P>
    P* Write(P* pData)
    {
        Vec2Template* pVector = (Vec2Template*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    
    
};


//  typedef
typedef Vec2Template<bool>      Vec2b;
typedef Vec2Template<float>     Vec2;
typedef Vec2Template<int>       Point2;
    

} // namespace t3

#endif // TRI_VEC2_HPP_INCLUDED