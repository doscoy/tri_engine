////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_vec2.hpp
    二次元ベクトル.
*/

#ifndef TRI_VEC2_HPP_INCLUDED
#define TRI_VEC2_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_math_util.hpp"
#include <iostream>


TRI_CORE_NS_BEGIN


///
/// Vec2
class Vec2 {
    using element_t = float;
public:
    element_t x_;   ///< x要素
    element_t y_;   ///< y要素
    
public:
    ///
    ///  コンストラクタ
    Vec2()
    {}
    
    ///
    /// コンストラクタ
    Vec2(const element_t ax, const element_t ay)
        : x_(ax)
        , y_(ay)
    {}
    
    ///
    /// デストラクタ
    ~Vec2(){}
    

public:
    ///
    /// x加算
    void addX(element_t v) {
        x_ += v;
    }

    ///
    /// y加算
    void addY(element_t v) {
        y_ += v;
    }
    
    ///
    /// 加算
    void add(Vec2& rhs) {
        addX(rhs.x_);
        addY(rhs.y_);
    }
    
    ///
    ///  内積
    element_t dotProduct( const Vec2& rhs ){
        return x_ * rhs.x_ + y_ * rhs.y_;
    }
    
    ///
    ///  ブレンド
    Vec2& blend( 
        const float t,
        const Vec2& v
    ) {
        x_ = x_ * (1 - t) + v.x_ * t;
        y_ = y_ * (1 - t) + v.y_ * t;
        return *this;
    }
    
    ///
    ///  正規化
    void normalize()
    {
        normalize( *this, *this );
    }
    
    ///
    ///  正規化したベクトルを取得
    Vec2 getNormalized() const {
        Vec2 rhs = *this;
        rhs.normalize();
        return rhs;
    }
    
    ///
    ///  長さの二乗
    element_t lengthSquare() const {
        return t3::hypotenuseSquare(x_, y_);
    }
    
    ///
    ///  長さ
    element_t length() const {
        return t3::hypotenuse(x_, y_);
    }
    
    ///
    ///  反転
    void reverse() {
        x_ = -x_;
        y_ = -y_;
    }
    
    ///
    ///  x_軸反転
    void reverseX() {
        x_ = -x_;
    }
    
    ///
    ///  y_軸反転
    void reverseY() {
        y_ = -y_;
    }
    
    ///
    ///  反転ベクトル取得
    Vec2 getReversed() const {
        
        return Vec2( -x_, -y_ );
    }
    
    
    ///
    /// ハーフベクトルを返す
    Vec2 half() const {
        return *this * 0.5f;
    }
    
    
    ///
    ///  pointer
    const element_t* pointer() const {
        return &x_;
    }
    
    ///
    ///  Vec2 = Vec2
    Vec2& operator =( const Vec2& rhs ){
        x_ = rhs.x_;
        y_ = rhs.y_;
        
        return *this;
    }

    
    ///
    ///  vec2 + vec2
    Vec2 operator +(const Vec2& rhs) const {
        return Vec2(x_ + rhs.x_, y_ + rhs.y_);
    }
    
    ///
    ///  vec2 - vec2
    Vec2 operator -(const Vec2& rhs) const {
        return Vec2(x_ - rhs.x_, y_ - rhs.y_);
    }
    
    ///
    ///  vec2 * vec2
    Vec2 operator *(const Vec2& rhs) const {
        return Vec2(x_ * rhs.x_, y_ * rhs.y_);
    }
    
    ///
    ///  vec2 / vec2
    Vec2 operator /(const Vec2& rhs) const {
        return Vec2(x_ / rhs.x_, y_ / rhs.y_);
    }
    
    ///
    ///  Vec2 / s
    Vec2 operator /( const float s ) const {
        float tmp = 1.0f / s;
        return Vec2( x_ * tmp, y_ * tmp );
    }
    
    ///
    ///  Vec2 * s
    Vec2 operator *( const float s ) const {
        return Vec2( x_ * s, y_ * s );
    }
    
    ///
    ///  Vec2 += Vec2
    void operator +=( const Vec2& rhs ) {
        x_ += rhs.x_;
        y_ += rhs.y_;
    }
    
    ///
    ///  Vec2 -= Vec2
    void operator -=( const Vec2& rhs ) {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
    }
    
    ///
    ///  Vec2 *= Vec2
    void operator *=( const Vec2& rhs ) {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
    }
    
    ///
    ///  Vec2 /= Vec2
    void operator /=( const Vec2& rhs ) {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
    }
    
    ///
    ///  Vec2 /= s
    void operator /=( const float s ) {
        float tmp = 1.0f / s;
        x_ *= tmp;
        y_ *= tmp;
    }
    
    ///
    ///  Vec2 *= s
    void operator *=( const float s ) {
        x_ *= s;
        y_ *= s;
    }

    
    ///
    ///  +Vec2
    Vec2 operator +() const {
        return *this;
    }
 
    ///
    ///  -Vec2
    Vec2 operator -() const {
        return Vec2( -x_, -y_ );
    }
    
    ///
    ///  cast
    operator element_t*() {
        return &x_;
    }
    
    ///
    ///  cast const
    operator const element_t*() const {
        return &x_;
    }
    
    ///
    ///  Vec2 == Vec2
    bool operator==(const Vec2& v) const {
        return isEqualFloat(x_, v.x_) && isEqualFloat(y_, v.y_);
    }
    

public:
    ///
    /// 内積
    static element_t dotProduct(
        const Vec2& v1,
        const Vec2& v2
    ){
        return v1.x_ * v2.x_ + v1.y_ * v2.y_;
    }
    
    ///
    /// 正規化
    static Vec2& normalize(
        Vec2& dst,
        const Vec2& src
    ){
        float s = 1.0f / src.length();
        dst.x_ *= s;
        dst.y_ *= s;
        return dst;
    }
    
    ///
    ///  ベクトル同士の距離を算出
    static element_t distance(
        const Vec2& v1,
        const Vec2& v2
    ){
        return sqrtf( distanceSquare( v1, v2 ) );
    }
    
    ///
    ///  ベクトル同士の距離の二乗を算出
    static element_t distanceSquare(
        const Vec2& v1,
        const Vec2& v2
    ){
        Vec2 tmp = v1 - v2;
        return ( tmp.lengthSquare() );
    }
    
    ///
    ///  同じ方向を向いているベクトルか判定
    static bool isSameDirection(
        const Vec2& v1,
        const Vec2& v2,
        const element_t score = 0.1f
    ){
        element_t dotv = dotProduct(v1, v2);
        return dotv >= score;
    }

    ///
    ///  ベクトル同士のブレンド
    static Vec2 getBlendVector(
        const float t,
        const Vec2& v1,
        const Vec2& v2
    ){
        return Vec2(
            v1.x_ * (1 - t) + v2.x_ * t,
            v1.y_ * (1 - t) + v2.y_ * t
        );
    }
 
    ///
    /// ゼロベクトル
    static Vec2 zero() {
        return Vec2(0, 0);
    }
    
    ///
    /// x軸ベクトルを生成
    static Vec2 axisX() {
        return Vec2(1, 0);
    }

    ///
    /// y軸ベクトルを生成
    static Vec2 axisY() {
        return Vec2(0, 1);
    }

};

    

TRI_CORE_NS_END

#endif // TRI_VEC2_HPP_INCLUDED

