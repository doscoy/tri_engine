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
/// Vec3Template
template <class VecType, class element_t>
class Vec3Template
{
public:
    element_t x_;   ///< x要素
    element_t y_;   ///< y要素
    element_t z_;   ///< z要素

public:
    ///
    ///  コンストラクタ
    Vec3Template()
    {}
    
    
    ///
    /// コンストラクタ
    Vec3Template(
        element_t x,
        element_t y,
        element_t z
    )   : x_(x)
        , y_(y)
        , z_(z)
    {}
    
    ///
    /// コンストラクタ
    Vec3Template(const VecType& rhs)
        : x_(rhs.x_)
        , y_(rhs.y_)
        , z_(rhs.z_)
    {}

    ///
    /// コンストラクタ
    Vec3Template(const Vec2& rhs)
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
    void add(const VecType& rhs) {
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
    VecType getNormalized() const {
        VecType v(x_, y_, z_);
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
    VecType& blend( 
        const float t,
        const VecType& v
    ) {
        x_ = x_ * (1 - t) + v.x_ * t;
        y_ = y_ * (1 - t) + v.y_ * t;
        z_ = z_ * (1 - t) + v.z_ * t;
        return *this;
    }
    
    ///
    ///  外積
    VecType crossProduct(
        const Vec3Template& v 
    ) const {
        return crossProduct(
            *this, v
        );
    }
    
    ///
    ///  内積
    element_t dotProduct(const VecType& v) const {
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
    VecType getReverse() const {
        return VecType( -x_, -y_, -z_ );
    }
    
    ///
    ///  距離を取得
    element_t distance(
        const VecType& target
    ) const {
        return distance( *this, target );
    }
    
    ///
    ///  距離の二乗を取得
    element_t distanceSquare(
        const VecType& target
    ) const {
        return distanceSquare( *this, target );
    }
    
    ///
    ///  Vec + Vec
    VecType operator +(const VecType& v) const {
        return VecType(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }
    
    ///
    ///  Vec - Vec
    VecType operator -(const VecType& v) const {
        return VecType(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }

    ///
    ///  Vec * Vec
    VecType operator *(const VecType& v) const {
        return VecType(x_ * v.x_, y_ * v.y_, z_ * v.z_);
    }
    
    ///
    ///  Vec / Vec
    VecType operator /(const VecType& v) const {
        return VecType(x_ / v.x_, y_ / v.y_, z_ / v.z_);
    }

    
    
    ///
    /// Vec * s
    VecType operator *(const element_t s) const {
        return VecType(x_ * s, y_ * s, z_ * s);
    }
    
    ///
    /// Vec / s
    VecType operator /(const element_t s) const {
        float tmp = 1.0f / s;
        return VecType(x_ * tmp, y_ * tmp, z_ * tmp);
    }

    ///
    ///  +Vec
    VecType operator +() const {
        return VecType(*this);
    }
    
    ///
    ///  -Vec
    VecType operator -() const {
        VecType tmp;
        tmp.x_ = -x_;
        tmp.y_ = -y_;
        tmp.z_ = -z_;
        return tmp;
    }
    
    ///
    ///  Vec += Vec
    void operator +=(const VecType& v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
    }
    
    ///
    ///  Vec -= Vec
    void operator -=(const VecType& v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
    }
    
    ///
    ///  Vec *= Vec
    void operator *=(const VecType& v) {
        x_ *= v.x_;
        y_ *= v.y_;
        z_ *= v.z_;
    }
    
    ///
    ///  Vec /= Vec
    void operator /=(const VecType& v) {
        x_ /= v.x_;
        y_ /= v.y_;
        z_ /= v.z_;
    }
    
    ///
    ///  Vec *= s
    void operator *=(element_t s) {
        x_ *= s;
        y_ *= s;
        z_ *= s;
    }
    
    ///
    ///  Vec /= s
    void operator /=(element_t s) {
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
    ///  Vec3Template == Vec3Template
    bool operator==(const VecType& v) const {
        return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
    }
    
public:

    ///
    /// ゼロベクトル
    static VecType zero() {
        return VecType(0, 0, 0);
    }
    
    ///
    /// x軸ベクトルを生成
    static VecType axisX() {
        return VecType(1, 0, 0);
    }

    ///
    /// y軸ベクトルを生成
    static VecType axisY() {
        return VecType(0, 1, 0);
    }

    ///
    /// z軸ベクトルを生成
    static VecType axisZ() {
        return VecType(0, 0, 1);
    }

    ///
    ///  内積計算
    static element_t dotProduct(
        const VecType& v1,
        const VecType& v2
    ){
        return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
    }
    
    ///
    ///  外積計算
    static VecType crossProduct(
        const Vec3Template& v1,
        const Vec3Template& v2
    ){
        return VecType(
            v1.y_ * v2.z_ - v1.z_ * v2.y_,
            v1.z_ * v2.x_ - v1.x_ * v2.z_,
            v1.x_ * v2.y_ - v1.y_ * v2.x_
        );
    }
    
    ///
    ///  正規化
    static void normalize(
        VecType& dst,
        const VecType& src
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
        const VecType& v1,
        const VecType& v2
    ){
        return sqrtf(distanceSquare(v1, v2));
    }
    
    ///
    ///  距離の二乗算出
    static element_t distanceSquare(
        const VecType& v1,
        const VecType& v2
    ){
        VecType tmp = v1 - v2;
        return tmp.lengthSquare();
    }
    
    ///
    ///  ベクトル同士のブレンド
    static VecType getBlendVector(
        const float t,
        const VecType& v1,
        const VecType& v2
    ){
        return VecType(
            v1.x_ * (1 - t) + v2.x_ * t,
            v1.y_ * (1 - t) + v2.y_ * t,
            v1.z_ * (1 - t) + v2.z_ * t
        );
    }
 

};

///
/// 3次元座標
struct Vec3
    : public Vec3Template<Vec3, float>
{
    Vec3() {}
	Vec3(
		float x,
		float y,
		float z
	)	: Vec3Template(x, y, z)
	{}
};

using Position3D = Vec3;


inline Vec3 operator *(float s, const Vec3& v) {
    return v * s;
}

inline Vec3 operator /(float s, const Vec3& v) {
    return v / s;
}





///
///	3次元拡大倍率
struct Scale3D
	: public Vec3Template<Scale3D, float>
{
	Scale3D(
		float x,
		float y,
		float z
	)   : Vec3Template(x, y, z)
	{}

};

inline Vec3 operator *(const Vec3& lhs, const Scale3D& rhs) {
    return Vec3(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_);
}

inline Vec3 operator /(const Vec3& lhs, const Scale3D& rhs) {
    return Vec3(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_, lhs.z_ * rhs.z_);
}

///
/// 回転角
struct Rotation
    : public Vec3Template<Rotation, Degree>
{
	Rotation(
		float x,
		float y,
		float z
	)	: Vec3Template(x, y, z)
	{}

	Rotation(
		Degree x,
		Degree y,
		Degree z
	)	: Vec3Template(x, y, z)
	{}
};



TRI_CORE_NS_END



#endif // TRI_VEC3_HPP_INCLUDED

