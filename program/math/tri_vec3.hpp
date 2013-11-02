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
#include <iostream>


namespace t3 {

template <typename T>
struct Vec3Template {
    T x;
    T y;
    T z;
    
    //  コンストラクタ
    Vec3Template()
    {}
    
    Vec3Template( T x, T y, T z )
        : x(x)
        , y(y)
        , z(z)
    {}
    
    Vec3Template( const Vec3Template& rhs )
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
    Vec3Template getNormalized() const {
        Vec3Template v = *this;
        v.normalize();
        return v;
    }
    
    //  ブレンド
    Vec3Template& blend( 
        const float t,
        const Vec3Template& v
    ) {
        x = x * (1 - t) + v.x * t;
        y = y * (1 - t) + v.y * t;
        z = z * (1 - t) + v.z * t;
        return *this;
    }
    
    //  外積
    Vec3Template crossProduct( const Vec3Template& v ) const {
        return Vec3Template( y * v.z - z * v.y,
                     z * v.x - x * v.z,
                     x * v.y - y * v.x );
    }
    
    //  内積
    T dotProduct( const Vec3Template& v ) const {
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
    Vec3Template getReverse() const {
        return Vec3Template( -x, -y, -z );
    }
    
    //  距離を取得
    T distance(
        const Vec3Template& target
    ) const {
        return distance( *this, target );
    }
    
    //  距離の二乗を取得
    T distanceSquare(
        const Vec3Template& target
    ) const {
        return distanceSquare( *this, target );
    }
    
    //  Vec + Vec
    Vec3Template operator +( const Vec3Template& v ) const {
        return Vec3Template( x + v.x, y + v.y, z + v.z );
    }
    
    //  Vec - Vec
    Vec3Template operator -( const Vec3Template& v ) const {
        return Vec3Template( x - v.x, y - v.y, z - v.z );
    }
    
    //  Vec * s
//    Vec3Template operator *( const T s ) const {
//        return Vec3Template( x * s, y * s, z * s );
//    }
    
    
    //  Vec / s
//    Vec3Template operator /( const T s ) const {
//        float tmp = 1.0f / s;
//        return Vec3Template( x * tmp, y * tmp, z * tmp );
//    }
    
    //  +Vec
    Vec3Template operator +() const {
        return Vec3Template( *this );
    }

    //  -Vec
    Vec3Template operator -() const {
        Vec3Template tmp;
        tmp.x = x;
        tmp.x = -x;
        tmp.y = -y;
        tmp.z = -z;
        return tmp;
    }
    
    //  Vec += Vec
    void operator +=( const Vec3Template& v ) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    
    //  Vec -= Vec
    void operator -=( const Vec3Template& v ) {
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

    //  Vec3Template == Vec3Template
    bool operator==(const Vec3Template& v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    
public:
    //  外積計算
    static T getDotProduct(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    
    //  外積計算
    static Vec3Template& getCrossProduct(
        Vec3Template& dst,
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        dst.x = v1.y * v2.z - v1.z * v2.y;
        dst.y = v1.z * v2.x - v1.x * v2.z;
        dst.z = v1.x * v2.y - v1.y * v2.x;
        return dst;
    }
    
    //  正規化
    static Vec3Template& normalize(
        Vec3Template& dst,
        const Vec3Template& src
    ){
        T length = src.length();
        T tmp = 1.0f / length;
        dst.x = src.x * tmp;
        dst.y = src.y * tmp;
        dst.z = src.z * tmp;
    }
    
    //  距離の算出
    static T distance(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return sqrtf( distanceSquare( v1, v2 ) );
    }
    
    //  距離の二乗算出
    static T distanceSquare(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        Vec3Template tmp = v1 - v2;
        return tmp.lengthSquare();
    }
    
    //  dump
    void dump() const {
        std::cout << "x:" << x << " y:" << y << " z:" << z << std::endl;
    }
    
    template <typename P>
    P* Write(P* pData)
    {
        Vec3Template* pVector = (Vec3Template*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
    
    //  ベクトル同士のブレンド
    static Vec3Template getBlendVector(
        const float t,
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return Vec3Template(
            v1.x * (1 - t) + v2.x * t,
            v1.y * (1 - t) + v2.y * t,
            v1.z * (1 - t) + v2.z * t
        );
    }

};


template <class T>
Vec3Template<T> operator *(const Vec3Template<T>& v, T s) {
    return Vec3Template<T>(v.x * s, v.y * s, v.z * s);
}

template <class T>
Vec3Template<T> operator *(T s, const Vec3Template<T>& v) {
    return Vec3Template<T>(v.x * s, v.y * s, v.z * s);
}
template <class T>
Vec3Template<T> operator /(const Vec3Template<T>& v, T s) {
    return Vec3Template<T>(v.x / s, v.y / s, v.z / s);
}

template <class T>
Vec3Template<T> operator /(T s, const Vec3Template<T>& v) {
    return Vec3Template<T>(v.x / s, v.y / s, v.z / s);
}




//  typedef
typedef Vec3Template<float>   Vec3;
typedef Vec3Template<int>     Point3;

}   // namespace t3



#endif // TRI_VEC3_HPP_INCLUDED
