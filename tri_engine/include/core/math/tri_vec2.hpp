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
#include "../debug/tri_assert.hpp"

TRI_CORE_NS_BEGIN


///
/// Vec2Template
template <class VecType, class element_t>
class Vec2Template {
public:
    element_t x_;   ///< x要素
    element_t y_;   ///< y要素
    
public:
    ///
    ///  コンストラクタ
    Vec2Template()
    {}
    
    ///
    /// コンストラクタ
    Vec2Template(
        const element_t ax, 
        const element_t ay
    )   : x_(ax)
        , y_(ay)
    {}
    
    ///
    /// デストラクタ
    ~Vec2Template(){}
    

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
    void add(Vec2Template& rhs) {
        addX(rhs.x_);
        addY(rhs.y_);
    }
    
    ///
    ///  内積
    element_t dotProduct(const Vec2Template& rhs){
        return x_ * rhs.x_ + y_ * rhs.y_;
    }
    
    ///
    ///  ブレンド
    Vec2Template& blend( 
        const float t,
        const Vec2Template& v
    ) {
        x_ = x_ * (1 - t) + v.x_ * t;
        y_ = y_ * (1 - t) + v.y_ * t;
        return *this;
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
    ///  正規化
    void normalize()
    {
        float len = length();
        T3_ASSERT(!isZeroFloat(len));
        float s = 1.0f / len;
        x_ *= s;
        y_ *= s;
    }
    
    ///
    ///  正規化したベクトルを取得
    Vec2Template getNormalized() const {
        Vec2Template rhs = *this;
        rhs.normalize();
        return rhs;
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
    VecType getReversed() const {
        
        return VecType( -x_, -y_ );
    }
    
    
    ///
    /// ハーフベクトルを返す
    VecType half() const {
        return *this * 0.5f;
    }
    
    
    ///
    ///  pointer
    const element_t* pointer() const {
        return &x_;
    }
    
    ///
    ///  Vec2Template = Vec2Template
    VecType& operator =( const VecType& rhs ){
        x_ = rhs.x_;
        y_ = rhs.y_;
        
        return static_cast<VecType&>(*this);
    }

    
    ///
    ///  vec2 + vec2
    VecType operator +(const VecType& rhs) const {
        return VecType(x_ + rhs.x_, y_ + rhs.y_);
    }
    
    ///
    ///  vec2 - vec2
    VecType operator -(const VecType& rhs) const {
        return VecType(x_ - rhs.x_, y_ - rhs.y_);
    }
    
    ///
    ///  vec2 * vec2
    VecType operator *(const VecType& rhs) const {
        return VecType(x_ * rhs.x_, y_ * rhs.y_);
    }
    
    ///
    ///  vec2 / vec2
    VecType operator /(const VecType& rhs) const {
        return VecType(x_ / rhs.x_, y_ / rhs.y_);
    }
    
    ///
    ///  Vec2Template / s
    VecType operator /(const element_t s) const {
        float tmp = 1.0f / s;
        return VecType( x_ * tmp, y_ * tmp );
    }
    
    ///
    ///  Vec2Template * s
    VecType operator *(const element_t s) const {
        return VecType( x_ * s, y_ * s );
    }
    
    ///
    ///  Vec2Template += Vec2Template
    VecType& operator +=(const VecType& rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return static_cast<VecType&>(*this);
    }
    
    ///
    ///  Vec2Template -= Vec2Template
    VecType& operator -=(const VecType& rhs) {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        return static_cast<VecType&>(*this);
    }
    
    ///
    ///  Vec2Template *= Vec2Template
    VecType& operator *=(const VecType& rhs) {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        return static_cast<VecType&>(*this);
    }
    
    ///
    ///  Vec2Template /= Vec2Template
    VecType& operator /=(const VecType& rhs) {
        x_ /= rhs.x_;
        y_ /= rhs.y_;
        return static_cast<VecType&>(*this);
    }
    
    ///
    ///  Vec2Template /= s
    VecType& operator /=(const element_t s) {
        float tmp = 1.0f / s;
        x_ *= tmp;
        y_ *= tmp;
        return static_cast<VecType&>(*this);
    }
    
    ///
    ///  Vec2Template *= s
    VecType& operator *=(const element_t s) {
        x_ *= s;
        y_ *= s;
        return static_cast<VecType&>(*this);
    }

    
    ///
    ///  +Vec2Template
    VecType operator +() const {
        return *this;
    }
 
    ///
    ///  -Vec2Template
    VecType operator -() const {
        return VecType( -x_, -y_ );
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
    ///  Vec2Template == Vec2Template
    bool operator==(const VecType& v) const {
        return isEqualFloat(x_, v.x_) && isEqualFloat(y_, v.y_);
    }
    

public:
    ///
    /// 内積
    static element_t dotProduct(
        const VecType& v1,
        const VecType& v2
    ){
        return v1.x_ * v2.x_ + v1.y_ * v2.y_;
    }
    
    ///
    /// 正規化
    static VecType& normalize(
        VecType& dst,
        const VecType& src
    ){
        float s = 1.0f / src.length();
        dst.x_ *= s;
        dst.y_ *= s;
        return dst;
    }
    
    ///
    ///  ベクトル同士の距離を算出
    static element_t distance(
        const VecType& v1,
        const VecType& v2
    ){
        return sqrtf( distanceSquare( v1, v2 ) );
    }
    
    ///
    ///  ベクトル同士の距離の二乗を算出
    static element_t distanceSquare(
        const VecType& v1,
        const VecType& v2
    ){
        VecType tmp = v1 - v2;
        return ( tmp.lengthSquare() );
    }
    
    ///
    ///  同じ方向を向いているベクトルか判定
    static bool isSameDirection(
        const VecType& v1,
        const VecType& v2,
        const element_t score = 0.1f
    ){
        element_t dotv = dotProduct(v1, v2);
        return dotv >= score;
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
            v1.y_ * (1 - t) + v2.y_ * t
        );
    }
 
    ///
    /// ゼロベクトル
    static VecType zero() {
        return VecType(0, 0);
    }
    
    ///
    /// x軸ベクトルを生成
    static VecType axisX() {
        return VecType(1, 0);
    }

    ///
    /// y軸ベクトルを生成
    static VecType axisY() {
        return VecType(0, 1);
    }

};



///
/// 2次元座標
struct Scale2D;
struct Vec2
    : public Vec2Template<Vec2, float>
{
    Vec2() {}
    
    Vec2(const Vec2& rhs)
        : Vec2Template(rhs.x_, rhs.y_)
    {}

	Vec2(
		float x,
		float y
	)	: Vec2Template(x, y)
	{}

    Vec2& operator *=(const Scale2D& rhs);

    ///
    ///  Vec2Template *= Vec2Template
    Vec2& operator *=(const Vec2& rhs) {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        return static_cast<Vec2&>(*this);
    }
};


using Position2D = Vec2;


inline Vec2 operator *(float s, const Vec2& v) {
    return v * s;
}

inline Vec2 operator /(float s, const Vec2& v) {
    return v / s;
}


///
/// 2次元拡大倍率
struct Scale2D
	: public Vec2Template<Scale2D, float>
{
    Scale2D(
        float x,
        float y
    )   : Vec2Template(x, y)
	{}

};

inline Vec2 operator *(const Vec2& lhs, const Scale2D& rhs) {
    return Vec2(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
}

inline Vec2 operator /(const Vec2& lhs, const Scale2D& rhs) {
    return Vec2(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_);
}

    

TRI_CORE_NS_END

#endif // TRI_VEC2_HPP_INCLUDED

