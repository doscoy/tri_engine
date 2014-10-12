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
    T x_;
    T y_;
    
    //  コンストラクタ
    Vec2Template()
    {}
    
    Vec2Template(const T ax, const T ay)
        : x_(ax)
        , y_(ay)
    {}
    
    template<typename O>
    Vec2Template<T>( const Vec2Template<O>& rhs )
        : x_( rhs.x_ )
        , y_( rhs.y_ )
    {
    }

   
 
    ~Vec2Template(){}
    
    //  内積
    T dotProduct( const Vec2Template& rhs ){
        return x_ * rhs.x_ + y_ * rhs.y_;
    }
    
    //  ブレンド
    Vec2Template& blend( 
        const float t,
        const Vec2Template& v
    ) {
        x_ = x_ * (1 - t) + v.x_ * t;
        y_ = y_ * (1 - t) + v.y_ * t;
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
        return ( x_*x_ + y_*y_ );
    }
    
    //  長さ
    T length() const {
        return t3::sqrtf( lengthSquare() );
    }
    
    //  反転
    void reverse() {
        x_ = -x_;
        y_ = -y_;
    }
    
    //  x_軸反転
    void reverseX() {
        x_ = -x_;
    }
    
    //  y_軸反転
    void reverseY() {
        y_ = -y_;
    }
    
    //  反転ベクトル取得
    Vec2Template getReversed() const {
        
        return Vec2( -x_, -y_ );
    }
    
    //  pointer
    const T* pointer() const {
        return &x_;
    }
    
    //  Vec2Template = Vec2Template
    Vec2Template& operator =( const Vec2Template& rhs ){
        x_ = rhs.x_;
        y_ = rhs.y_;
        
        return *this;
    }

        
    //  vec2 + vec2
    Vec2Template operator +(const Vec2Template& rhs) const {
        return Vec2Template(x_ + rhs.x_, y_ + rhs.y_);
    }
    
    //  vec2 - vec2
    Vec2Template operator -(const Vec2Template& rhs) const {
        return Vec2Template(x_ - rhs.x_, y_ - rhs.y_);
    }
    
    //  vec2 * vec2
    Vec2Template operator *(const Vec2Template& rhs) const {
        return Vec2Template(x_ * rhs.x_, y_ * rhs.y_);
    }
    
    //  vec2 / vec2
    Vec2Template operator /(const Vec2Template& rhs) const {
        return Vec2Template(x_ / rhs.x_, y_ / rhs.y_);
    }
    
    
     //  Vec2Template / s
    Vec2Template operator /( const float s ) const {
        float tmp = 1.0f / s;
        return Vec2Template( x_ * tmp, y_ * tmp );
    }
    
    //  Vec2Template * s
    Vec2Template operator *( const float s ) const {
        return Vec2Template( x_ * s, y_ * s );
    }
    
    
    //  Vec2Template += Vec2Template
    void operator +=( const Vec2Template& rhs ) {
        x_ += rhs.x_;
        y_ += rhs.y_;
    }
    
    //  Vec2Template -= Vec2Template
    void operator -=( const Vec2Template& rhs ) {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
    }
    
    //  Vec2Template *= Vec2Template
    void operator *=( const Vec2Template& rhs ) {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
    }
    
    //  Vec2Template /= Vec2Template
    void operator /=( const Vec2Template& rhs ) {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
    }
    
    
    
    
    //  Vec2Template /= s
    void operator /=( const float s ) {
        float tmp = 1.0f / s;
        x_ *= tmp;
        y_ *= tmp;
    }
    
    //  Vec2Template *= s
    void operator *=( const float s ) {
        x_ *= s;
        y_ *= s;
    }

    
    
    //  +Vec2Template
    Vec2Template operator +() const {
        return *this;
    }
 
    //  -Vec2Template
    Vec2Template operator -() const {
        return Vec2Template( -x_, -y_ );
    }
    
    //  cast
    operator T*() {
        return &x_;
    }
    
    //  cast const
    operator const T*() const {
        return &x_;
    }
    
    //  Vec2Template == Vec2Template
    bool operator==(const Vec2Template& v) const {
        return x_ == v.x_ && y_ == v.y_;
    }

public:
    static T dotProduct(
        const Vec2Template& v1,
        const Vec2Template& v2
    ){
        return v1.x_ * v2.x_ + v1.y_ * v2.y_;
    }
    
    static Vec2Template& normalize(
        Vec2Template& dst,
        const Vec2Template& src
    ){
        float s = 1.0f / src.length();
        dst.x_ *= s;
        dst.y_ *= s;
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
            v1.x_ * (1 - t) + v2.x_ * t,
            v1.y_ * (1 - t) + v2.y_ * t
        );
    }

/*
    template <typename P>
    P* Write(P* pData)
    {
        Vec2Template* pVector = (Vec2Template*) pData;
        *pVector++ = *this;
        return (P*) pVector;
    }
*/    
    
};


//  typedef
typedef Vec2Template<bool>      Vec2b;
typedef Vec2Template<float>     Vec2;
    

} // namespace t3

#endif // TRI_VEC2_HPP_INCLUDED