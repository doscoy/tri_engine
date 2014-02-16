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
inline namespace math {

template <typename T>
struct Vec3Template {
    T x_;
    T y_;
    T z_;
    
    //  コンストラクタ
    Vec3Template()
    {}
    
    Vec3Template( T x, T y, T z )
        : x_(x)
        , y_(y)
        , z_(z)
    {}
    
    Vec3Template( const Vec3Template& rhs )
        : x_(rhs.x_)
        , y_(rhs.y_)
        , z_(rhs.z_)
    {}
    
    //  長さの二乗を取得
    T lengthSquare() const {
        return x_ * x_ + y_ * y_ + z_ * z_;
    }
    
    //  長さを取得
    T length() const {
        return t3::sqrtf( lengthSquare() );
    }
    
    //  正規化
    void normalize(){
        float s = 1.0f / length();
        x_ *= s;
        y_ *= s;
        z_ *= s;
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
        x_ = x_ * (1 - t) + v.x_ * t;
        y_ = y_ * (1 - t) + v.y_ * t;
        z_ = z_ * (1 - t) + v.z_ * t;
        return *this;
    }
    
    //  外積
    Vec3Template crossProduct( const Vec3Template& v ) const {
        return Vec3Template(
            y_ * v.z_ - z_ * v.y_,
            z_ * v.x_ - x_ * v.z_,
            x_ * v.y_ - y_ * v.x_
        );
    }
    
    //  内積
    T dotProduct( const Vec3Template& v ) const {
        return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
    }
    
    //  ベクトルの反転
    void reverse() {
        x_ = -x_;
        y_ = -y_;
        z_ = -z_;
    }
    
    //  x軸の反転
    void reverseX() {
        x_ = -x_;
    }
    
    //  y軸の反転
    void reverseY() {
        y_ = -y_;
    }
    
    //  z軸の反転
    void reverseZ() {
        z_ = -z_;
    }
    
    //  反転ベクトルの取得
    Vec3Template getReverse() const {
        return Vec3Template( -x_, -y_, -z_ );
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
        return Vec3Template(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }
    
    //  Vec - Vec
    Vec3Template operator -( const Vec3Template& v ) const {
        return Vec3Template(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }
    
    //  +Vec
    Vec3Template operator +() const {
        return Vec3Template( *this );
    }

    //  -Vec
    Vec3Template operator -() const {
        Vec3Template tmp;
        tmp.x_ = -x_;
        tmp.y_ = -y_;
        tmp.z_ = -z_;
        return tmp;
    }
    
    //  Vec += Vec
    void operator +=( const Vec3Template& v ) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
    }
    
    //  Vec -= Vec
    void operator -=( const Vec3Template& v ) {
        x_ -= v.x;
        y_ -= v.y;
        z_ -= v.z;
    }
    
    //  Vec *= s
    void operator *=( T s ) {
        x_ *= s;
        y_ *= s;
        z_ *= s;
    }
    
    //  Vec /= s
    void operator /=( T s ) {
        float tmp = 1.0f / s;
        x_ *= tmp;
        y_ *= tmp;
        z_ *= tmp;
    }
    
    // pointer
    const T* pointer() const {
        return &x_;
    }

    //  Vec3Template == Vec3Template
    bool operator==(const Vec3Template& v) const {
        return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
    }
    
public:
    //  外積計算
    static T getDotProduct(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
    }
    
    //  外積計算
    static Vec3Template& getCrossProduct(
        Vec3Template& dst,
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        dst.x_ = v1.y_ * v2.z_ - v1.z_ * v2.y_;
        dst.y_ = v1.z_ * v2.x_ - v1.x_ * v2.z_;
        dst.z_ = v1.x_ * v2.y_ - v1.y_ * v2.x_;
        return dst;
    }
    
    //  正規化
    static Vec3Template& normalize(
        Vec3Template& dst,
        const Vec3Template& src
    ){
        T length = src.length();
        T tmp = 1.0f / length;
        dst.x_ = src.x_ * tmp;
        dst.y_ = src.y_ * tmp;
        dst.z_ = src.z_ * tmp;
    }
    
    //  距離の算出
    static T distance(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return sqrtf(distanceSquare(v1, v2));
    }
    
    //  距離の二乗算出
    static T distanceSquare(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        Vec3Template tmp = v1 - v2;
        return tmp.lengthSquare();
    }
    
    //  ベクトル同士のブレンド
    static Vec3Template getBlendVector(
        const float t,
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return Vec3Template(
            v1.x_ * (1 - t) + v2.x_ * t,
            v1.y_ * (1 - t) + v2.y_ * t,
            v1.z_ * (1 - t) + v2.z_ * t
        );
    }
 

};


template <class T>
Vec3Template<T> operator *(const Vec3Template<T>& v, T s) {
    return Vec3Template<T>(v.x_ * s, v.y_ * s, v.z_ * s);
}

template <class T>
Vec3Template<T> operator *(T s, const Vec3Template<T>& v) {
    return Vec3Template<T>(v.x_ * s, v.y_ * s, v.z_ * s);
}
template <class T>
Vec3Template<T> operator /(const Vec3Template<T>& v, T s) {
    return Vec3Template<T>(v.x_ / s, v.y_ / s, v.z_ / s);
}

template <class T>
Vec3Template<T> operator /(T s, const Vec3Template<T>& v) {
    return Vec3Template<T>(v.x_ / s, v.y_ / s, v.z_ / s);
}




//  typedef
typedef Vec3Template<float>   Vec3;
typedef Vec3Template<int>     Point3;


}   // namespace math
}   // namespace t3



#endif // TRI_VEC3_HPP_INCLUDED