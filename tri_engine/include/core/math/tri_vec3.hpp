////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_vec3.hpp
    三次元ベクトル.
*/

#ifndef TRI_VEC3_HPP_INCLUDED
#define TRI_VEC3_HPP_INCLUDED

//  include
#include <iostream>

#include "core/core_config.hpp"
#include "../math/tri_math_util.hpp"
#include "../debug/tri_assert.hpp"
#include "core/math/tri_vec2.hpp"

TRI_CORE_NS_BEGIN

///
/// Vec3

class Vec3 {
    using element_t = float;
public:
    element_t x_;   ///< x要素
    element_t y_;   ///< y要素
    element_t z_;   ///< z要素

public:
    ///
    ///  コンストラクタ
    Vec3()
    {}
    
    
    ///
    /// コンストラクタ
    Vec3(
        element_t x,
        element_t y,
        element_t z
    )   : x_(x)
        , y_(y)
        , z_(z)
    {}
    
    ///
    /// コンストラクタ
    Vec3( const Vec3& rhs )
        : x_(rhs.x_)
        , y_(rhs.y_)
        , z_(rhs.z_)
    {}

    ///
    /// コンストラクタ
    Vec3(const Vec2& rhs)
        : x_(rhs.x_)
        , y_(rhs.y_)
        , z_(0.0f)
    {}



public:

    ///
    /// xを加算
    void addX(element_t v) {
        x_ += v;
    }

    ///
    /// yを加算
    void addY(element_t v) {
        y_ += v;
    }
    
    ///
    /// zを加算
    void addZ(element_t v) {
        z_ += v;
    }
    
    ///
    /// 加算
    void add(Vec3& rhs) {
        addX(rhs.x_);
        addY(rhs.y_);
        addZ(rhs.z_);
    }
    
    ///
    ///  長さの二乗を取得
    element_t lengthSquare() const {
        return t3::hypotenuseSquare(x_, y_, z_);
    }
    
    ///
    ///  長さを取得
    element_t length() const {
        return t3::hypotenuse(x_, y_, z_);
    }
    
    ///
    ///  正規化
    void normalize() {
        float len = length();
        T3_ASSERT(!isZeroFloat(len));
        float s = 1.0f / len;
        x_ *= s;
        y_ *= s;
        z_ *= s;
    }
    
    ///
    ///  正規化したベクトルを取得
    Vec3 getNormalized() const {
        Vec3 v = *this;
        v.normalize();
        return v;
    }
    
    ///
    /// 正規化されたベクトルか判定
    bool isNormalized() const {
        return isEqualFloat(length(), 1.0f);
    }

    ///
    ///  ブレンド
    Vec3& blend( 
        const float t,
        const Vec3& v
    ) {
        x_ = x_ * (1 - t) + v.x_ * t;
        y_ = y_ * (1 - t) + v.y_ * t;
        z_ = z_ * (1 - t) + v.z_ * t;
        return *this;
    }
    
    ///
    ///  外積
    Vec3 crossProduct(
        const Vec3& v 
    ) const {
        return crossProduct(
            *this, v
        );
    }
    
    ///
    ///  内積
    element_t dotProduct( const Vec3& v ) const {
        return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
    }
    
    ///
    ///  ベクトルの反転
    void reverse() {
        x_ = -x_;
        y_ = -y_;
        z_ = -z_;
    }
    
    ///
    ///  x軸の反転
    void reverseX() {
        x_ = -x_;
    }
    
    ///
    ///  y軸の反転
    void reverseY() {
        y_ = -y_;
    }
    
    ///
    ///  z軸の反転
    void reverseZ() {
        z_ = -z_;
    }
    
    ///
    ///  反転ベクトルの取得
    Vec3 getReverse() const {
        return Vec3( -x_, -y_, -z_ );
    }
    
    ///
    ///  距離を取得
    element_t distance(
        const Vec3& target
    ) const {
        return distance( *this, target );
    }
    
    ///
    ///  距離の二乗を取得
    element_t distanceSquare(
        const Vec3& target
    ) const {
        return distanceSquare( *this, target );
    }
    
    ///
    ///  Vec + Vec
    Vec3 operator +( const Vec3& v ) const {
        return Vec3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }
    
    ///
    ///  Vec - Vec
    Vec3 operator -( const Vec3& v ) const {
        return Vec3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }
    
    ///
    ///  +Vec
    Vec3 operator +() const {
        return Vec3( *this );
    }
    
    ///
    ///  -Vec
    Vec3 operator -() const {
        Vec3 tmp;
        tmp.x_ = -x_;
        tmp.y_ = -y_;
        tmp.z_ = -z_;
        return tmp;
    }
    
    ///
    ///  Vec += Vec
    void operator +=( const Vec3& v ) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
    }
    
    ///
    ///  Vec -= Vec
    void operator -=( const Vec3& v ) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
    }
    
    ///
    ///  Vec *= s
    void operator *=( element_t s ) {
        x_ *= s;
        y_ *= s;
        z_ *= s;
    }
    
    //  Vec /= s
    void operator /=( element_t s ) {
        float tmp = 1.0f / s;
        x_ *= tmp;
        y_ *= tmp;
        z_ *= tmp;
    }
    
    ///
    /// pointer
    const element_t* pointer() const {
        return &x_;
    }

    ///
    ///  Vec3 == Vec3
    bool operator==(const Vec3& v) const {
        return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
    }
    
public:

    ///
    /// ゼロベクトル
    static Vec3 zero() {
        return Vec3(0, 0, 0);
    }
    
    ///
    /// x軸ベクトルを生成
    static Vec3 axisX() {
        return Vec3(1, 0, 0);
    }

    ///
    /// y軸ベクトルを生成
    static Vec3 axisY() {
        return Vec3(0, 1, 0);
    }

    ///
    /// z軸ベクトルを生成
    static Vec3 axisZ() {
        return Vec3(0, 0, 1);
    }

    ///
    ///  外積計算
    static element_t dotProduct(
        const Vec3& v1,
        const Vec3& v2
    ){
        return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
    }
    
    ///
    ///  外積計算
    static Vec3 crossProduct(
        const Vec3& v1,
        const Vec3& v2
    ){
        return Vec3(
            v1.y_ * v2.z_ - v1.z_ * v2.y_,
            v1.z_ * v2.x_ - v1.x_ * v2.z_,
            v1.x_ * v2.y_ - v1.y_ * v2.x_
        );
    }
    
    ///
    ///  正規化
    static void normalize(
        Vec3& dst,
        const Vec3& src
    ){
        element_t length = src.length();
        element_t tmp = 1.0f / length;
        dst.x_ = src.x_ * tmp;
        dst.y_ = src.y_ * tmp;
        dst.z_ = src.z_ * tmp;
    }
    
    ///
    ///  距離の算出
    static element_t distance(
        const Vec3& v1,
        const Vec3& v2
    ){
        return sqrtf(distanceSquare(v1, v2));
    }
    
    ///
    ///  距離の二乗算出
    static element_t distanceSquare(
        const Vec3& v1,
        const Vec3& v2
    ){
        Vec3 tmp = v1 - v2;
        return tmp.lengthSquare();
    }
    
    ///
    ///  ベクトル同士のブレンド
    static Vec3 getBlendVector(
        const float t,
        const Vec3& v1,
        const Vec3& v2
    ){
        return Vec3(
            v1.x_ * (1 - t) + v2.x_ * t,
            v1.y_ * (1 - t) + v2.y_ * t,
            v1.z_ * (1 - t) + v2.z_ * t
        );
    }
 

};



///
/// オペレータ *
inline Vec3 operator *(const Vec3& v, float s) {
    return Vec3(v.x_ * s, v.y_ * s, v.z_ * s);
}

///
/// オペレータ *
inline Vec3 operator *(float s, const Vec3& v) {
    return Vec3(v.x_ * s, v.y_ * s, v.z_ * s);
}

///
/// オペレータ /
inline Vec3 operator /(const Vec3& v, float s) {
    return Vec3(v.x_ / s, v.y_ / s, v.z_ / s);
}

///
/// オペレータ /
inline Vec3 operator /(float s, const Vec3& v) {
    return Vec3(v.x_ / s, v.y_ / s, v.z_ / s);
}




TRI_CORE_NS_END



#endif // TRI_VEC3_HPP_INCLUDED

