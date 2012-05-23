/*
 *  tri_vec3.hpp
 *  TriEngine
 *
 *  Created by 可児 哲郎 on 11/09/22.
 *  Copyright 2011  . All rights reserved.
 *
 */

#ifndef TRI_VEC3_HPP_INCLUDED
#define TRI_VEC3_HPP_INCLUDED

#include "../math/tri_math_util.hpp"
#include "tri_basetypes.hpp"
#include <iostream>


namespace t3 {

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;
    
    //  コンストラクタ
    Vec3()
    {}
    
    Vec3( T x, T y, T z )
        : x(x)
        , y(y)
        , z(z)
    {}
    
    Vec3( const Vec3& rhs )
        : x(rhs.x)
        , y(rhs.y)
        , z(rhs.z)
    {}
    
    //  長さの二乗を取得
    T lengthSquare() const {
        return x*x + y*y + z*z;
    }
    
    //  長さを取得
    T length() const {
        return t3::sqrtf( lengthSquare() );
    }
    
    //  正規化
    void normalize(){
        float s = 1.0f / length();
        x *= s;
        y *= s;
        z *= s;
    }
    
    //  正規化したベクトルを取得
    Vec3 getNormalized() const {
        Vec3 v = *this;
        v.normalize();
        return v;
    }
    
    //  ブレンド
    Vec3& blend( 
        const float t,
        const Vec3& v
    ) {
        x = x * (1 - t) + v.x * t;
        y = y * (1 - t) + v.y * t;
        z = z * (1 - t) + v.z * t;
        return *this;
    }
    
    //  外積
    Vec3 crossProduct( const Vec3& v ) const {
        return Vec3( y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x );
    }
    
    //  内積
    T dotProduct( const Vec3& v ) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    //  ベクトルの反転
    void reverse() {
        x = -x;
        y = -y;
        z = -z;
    }
    
    //  x軸の反転
    void reverseX() {
        x = -x;
    }
    
    //  y軸の反転
    void reverseY() {
        y = -y;
    }
    
    //  z軸の反転
    void reverseZ() {
        z = -z;
    }
    
    //  反転ベクトルの取得
    Vec3 getReverse() const {
        return Vec3( -x, -y, -z );
    }
    
    //  距離を取得
    T distance(
        const Vec3& target
    ) const {
        return distance( *this, target );
    }
    
    //  距離の二乗を取得
    T distanceSquare(
        const Vec3& target
    ) const {
        return distanceSquare( *this, target );
    }
    
    //  Vec + Vec
    Vec3 operator +( const Vec3& v ) const {
        return Vec3( x + v.x, y + v.y, z + v.z );
    }
    
    //  Vec - Vec
    Vec3 operator -( const Vec3& v ) const {
        return Vec3( x - v.x, y - v.y, z - v.z );
    }
    
    //  Vec * s
    Vec3 operator *( const T s ) const {
        return Vec3( x * s, y * s, z * s );
    }
    
    //  Vec / s
    Vec3 operator /( const T s ) const {
        float tmp = 1.0f / s;
        return Vec3( x * tmp, y * tmp, z * tmp );
    }
    
    //  +Vec
    Vec3 operator +() const {
        return Vec3( *this );
    }

    //  -Vec
    Vec3 operator -() const {
        Vec3 tmp;
        tmp.x = x;
        tmp.x = -x;
        tmp.y = -y;
        tmp.z = -z;
        return tmp;
    }
    
    //  Vec += Vec
    void operator +=( const Vec3& v ) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    
    //  Vec -= Vec
    void operator -=( const Vec3& v ) {
        x -= v.x;
        y -= v.y;
        z -= v.z; 
    }
    
    //  Vec *= s
    void operator *=( T s ) {
        x *= s;
        y *= s;
        z *= s; 
    }
    
    //  Vec /= s
    void operator /=( T s ) {
        float tmp = 1.0f / s;
        x *= tmp;
        y *= tmp;
        z *= tmp;
    }
    
    // pointer
    const T* pointer() const {
        return &x;
    }

    //  Vec3 == Vec3
    bool operator==(const Vec3& v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    
public:
    //  外積計算
    static T getDotProduct(
        const Vec3& v1,
        const Vec3& v2
    ){
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    
    //  外積計算
    static Vec3& getCrossProduct(
        Vec3& dst,
        const Vec3& v1,
        const Vec3& v2
    ){
        dst.x = v1.y * v2.z - v1.z * v2.y;
        dst.y = v1.z * v2.x - v1.x * v2.z;
        dst.z = v1.x * v2.y - v1.y * v2.x;
        return dst;
    }
    
    //  正規化
    static Vec3& normalize(
        Vec3& dst,
        const Vec3& src
    ){
        T length = src.length();
        T tmp = 1.0f / length;
        dst.x = src.x * tmp;
        dst.y = src.y * tmp;
        dst.z = src.z * tmp;
    }
    
    //  距離の算出
    static T distance(
        const Vec3& v1,
        const Vec3& v2
    ){
        return sqrtf( distanceSquare( v1, v2 ) );
    }
    
    //  距離の二乗算出
    static T distanceSquare(
        const Vec3& v1,
        const Vec3& v2
    ){
        Vec3 tmp = v1 - v2;
        return tmp.lengthSquare();
    }
    
    //  dump
    void dump() const {
        std::cout << "x:" << x << " y:" << y << " z:" << z << std::endl;
    }
    
    template <typename P>
    P* Write(P* pData)
    {
        Vec3* pVector = (Vec3*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    
    //  ベクトル同士のブレンド
    static Vec3 getBlendVector(
        const float t,
        const Vec3& v1,
        const Vec3& v2
    ){
        return Vec3(
            v1.x * (1 - t) + v2.x * t,
            v1.y * (1 - t) + v2.y * t,
            v1.z * (1 - t) + v2.z * t
        );
    }

};


//  typedef
typedef Vec3<float>   vec3_t;
typedef Vec3<int>     ivec3_t;

}   // namespace t3



#endif // TRI_VEC3_HPP_INCLUDED
