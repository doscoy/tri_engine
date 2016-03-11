////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_matrix.hpp
    行列.
*/

#ifndef TRI_MATRIX_HPP_INCLUDED
#define TRI_MATRIX_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_math_types.hpp"
#include "tri_quaternion.hpp"
#include "../math/tri_math_util.hpp"
#include "../debug/tri_assert.hpp"

#include "tri_math_types.hpp"
#include "tri_vec4.hpp"

TRI_CORE_NS_BEGIN


///
/// 行列
class Mtx44 {
public:
    ///
    /// 行列初期化
    Mtx44()
        : x_(1,0,0,0)
        , y_(0,1,0,0)
        , z_(0,0,1,0)
        , w_(0,0,0,1)
    {}
    
    
    ///
    /// 行列初期化
    Mtx44(const float* m) {
        x_.x_ = m[0];  x_.y_ = m[1];  x_.z_ = m[2];  x_.w_ = m[3];
        y_.x_ = m[4];  y_.y_ = m[5];  y_.z_ = m[6];  y_.w_ = m[7];
        z_.x_ = m[8];  z_.y_ = m[9];  z_.z_ = m[10]; z_.w_ = m[11];
        w_.x_ = m[12]; w_.y_ = m[13]; w_.z_ = m[14]; w_.w_ = m[15];
    }

    ///
    /// 行列初期化
    Mtx44(
        float  a0, float  a1, float  a2, float  a3,
        float  a4, float  a5, float  a6, float  a7,
        float  a8, float  a9, float a10, float a11,
        float a12, float a13, float a14, float a15
    ) {
        x_.x_ =  a0;  x_.y_ =  a1;  x_.z_ =  a2;  x_.w_ =  a3;
        y_.x_ =  a4;  y_.y_ =  a5;  y_.z_ =  a6;  y_.w_ =  a7;
        z_.x_ =  a8;  z_.y_ =  a9;  z_.z_ = a10;  z_.w_ = a11;
        w_.x_ = a12;  w_.y_ = a13;  w_.z_ = a14;  w_.w_ = a15;
    }


    ///
    /// 行列初期化
    Mtx44(
        const Vec3 a,
        const Vec3 b,
        const Vec3 c,
        const Vec3 d
    )   : x_(a)
        , y_(b)
        , z_(c)
        , w_(d)
    {}
    
    
    ///
    /// 行列同士の掛け算
    Mtx44 operator * (const Mtx44& r) const {
        return multiply(*this, r);
    }

    ///
    /// 行列同士の掛け算
    static Mtx44 multiply(
        const Mtx44& l,
        const Mtx44& r
    ) {
        Mtx44 m;
/*
        //  S * R * T
        m.x_.x_ = l.x_.x_ * r.x_.x_ + l.x_.y_ * r.y_.x_ + l.x_.z_ * r.z_.x_ + l.x_.w_ * r.w_.x_;
        m.x_.y_ = l.x_.x_ * r.x_.y_ + l.x_.y_ * r.y_.y_ + l.x_.z_ * r.z_.y_ + l.x_.w_ * r.w_.y_;
        m.x_.z_ = l.x_.x_ * r.x_.z_ + l.x_.y_ * r.y_.z_ + l.x_.z_ * r.z_.z_ + l.x_.w_ * r.w_.z_;
        m.x_.w_ = l.x_.x_ * r.x_.w_ + l.x_.y_ * r.y_.w_ + l.x_.z_ * r.z_.w_ + l.x_.w_ * r.w_.w_;
      
        m.y_.x_ = l.y_.x_ * r.x_.x_ + l.y_.y_ * r.y_.x_ + l.y_.z_ * r.z_.x_ + l.y_.w_ * r.w_.x_;
        m.y_.y_ = l.y_.x_ * r.x_.y_ + l.y_.y_ * r.y_.y_ + l.y_.z_ * r.z_.y_ + l.y_.w_ * r.w_.y_;
        m.y_.z_ = l.y_.x_ * r.x_.z_ + l.y_.y_ * r.y_.z_ + l.y_.z_ * r.z_.z_ + l.y_.w_ * r.w_.z_;
        m.y_.w_ = l.y_.x_ * r.x_.w_ + l.y_.y_ * r.y_.w_ + l.y_.z_ * r.z_.w_ + l.y_.w_ * r.w_.w_;
        
        m.z_.x_ = l.z_.x_ * r.x_.x_ + l.z_.y_ * r.y_.x_ + l.z_.z_ * r.z_.x_ + l.z_.w_ * r.w_.x_;
        m.z_.y_ = l.z_.x_ * r.x_.y_ + l.z_.y_ * r.y_.y_ + l.z_.z_ * r.z_.y_ + l.z_.w_ * r.w_.y_;
        m.z_.z_ = l.z_.x_ * r.x_.z_ + l.z_.y_ * r.y_.z_ + l.z_.z_ * r.z_.z_ + l.z_.w_ * r.w_.z_;
        m.z_.w_ = l.z_.x_ * r.x_.w_ + l.z_.y_ * r.y_.w_ + l.z_.z_ * r.z_.w_ + l.z_.w_ * r.w_.w_;
        
        m.w_.x_ = l.w_.x_ * r.x_.x_ + l.w_.y_ * r.y_.x_ + l.w_.z_ * r.z_.x_ + l.w_.w_ * r.w_.x_;
        m.w_.y_ = l.w_.x_ * r.x_.y_ + l.w_.y_ * r.y_.y_ + l.w_.z_ * r.z_.y_ + l.w_.w_ * r.w_.y_;
        m.w_.z_ = l.w_.x_ * r.x_.z_ + l.w_.y_ * r.y_.z_ + l.w_.z_ * r.z_.z_ + l.w_.w_ * r.w_.z_;
        m.w_.w_ = l.w_.x_ * r.x_.w_ + l.w_.y_ * r.y_.w_ + l.w_.z_ * r.z_.w_ + l.w_.w_ * r.w_.w_;
*/
        //  T * R * S
        m.x_.x_ = l.x_.x_ * r.x_.x_ + l.y_.x_ * r.x_.y_ + l.z_.x_ * r.x_.z_ + l.w_.x_ * r.x_.w_;
        m.x_.y_ = l.x_.y_ * r.x_.x_ + l.y_.y_ * r.x_.y_ + l.z_.y_ * r.x_.z_ + l.w_.y_ * r.x_.w_;
        m.x_.z_ = l.x_.z_ * r.x_.x_ + l.y_.z_ * r.x_.y_ + l.z_.z_ * r.x_.z_ + l.w_.z_ * r.x_.w_;
        m.x_.w_ = l.x_.w_ * r.x_.x_ + l.y_.w_ * r.x_.y_ + l.z_.w_ * r.x_.z_ + l.w_.w_ * r.x_.w_;

        m.y_.x_ = l.x_.x_ * r.y_.x_ + l.y_.x_ * r.y_.y_ + l.z_.x_ * r.y_.z_ + l.w_.x_ * r.y_.w_;
        m.y_.y_ = l.x_.y_ * r.y_.x_ + l.y_.y_ * r.y_.y_ + l.z_.y_ * r.y_.z_ + l.w_.y_ * r.y_.w_;
        m.y_.z_ = l.x_.z_ * r.y_.x_ + l.y_.z_ * r.y_.y_ + l.z_.z_ * r.y_.z_ + l.w_.z_ * r.y_.w_;
        m.y_.w_ = l.x_.w_ * r.y_.x_ + l.y_.w_ * r.y_.y_ + l.z_.w_ * r.y_.z_ + l.w_.w_ * r.y_.w_;

        m.z_.x_ = l.x_.x_ * r.z_.x_ + l.y_.x_ * r.z_.y_ + l.z_.x_ * r.z_.z_ + l.w_.x_ * r.z_.w_;
        m.z_.y_ = l.x_.y_ * r.z_.x_ + l.y_.y_ * r.z_.y_ + l.z_.y_ * r.z_.z_ + l.w_.y_ * r.z_.w_;
        m.z_.z_ = l.x_.z_ * r.z_.x_ + l.y_.z_ * r.z_.y_ + l.z_.z_ * r.z_.z_ + l.w_.z_ * r.z_.w_;
        m.z_.w_ = l.x_.w_ * r.z_.x_ + l.y_.w_ * r.z_.y_ + l.z_.w_ * r.z_.z_ + l.w_.w_ * r.z_.w_;

        m.w_.x_ = l.x_.x_ * r.w_.x_ + l.y_.x_ * r.w_.y_ + l.z_.x_ * r.w_.z_ + l.w_.x_ * r.w_.w_;
        m.w_.y_ = l.x_.y_ * r.w_.x_ + l.y_.y_ * r.w_.y_ + l.z_.y_ * r.w_.z_ + l.w_.y_ * r.w_.w_;
        m.w_.z_ = l.x_.z_ * r.w_.x_ + l.y_.z_ * r.w_.y_ + l.z_.z_ * r.w_.z_ + l.w_.z_ * r.w_.w_;
        m.w_.w_ = l.x_.w_ * r.w_.x_ + l.y_.w_ * r.w_.y_ + l.z_.w_ * r.w_.z_ + l.w_.w_ * r.w_.w_;
        return m;

    }


    ///
    /// ベクトルと行列の掛け算
    Vec4 operator * (const Vec4& b) const {
        return xform(b);
    }
    
    ///
    /// ベクトルと行列の掛け算
    Vec3 xform(const Vec3& b) const {
        Vec4 a(b);
        Vec4 a2 = xform(a);
        Vec3 a3(a2.x_, a2.y_, a2.z_);
        return a3;
    }
    
    ///
    /// ベクトルと行列の掛け算
    Vec4 xform(const Vec4& b) const {
        Vec4 v;
        v.x_ = x_.x_ * b.x_ + x_.y_ * b.y_ + x_.z_ * b.z_ + x_.w_ * b.w_;
        v.y_ = y_.x_ * b.x_ + y_.y_ * b.y_ + y_.z_ * b.z_ + y_.w_ * b.w_;
        v.z_ = z_.x_ * b.x_ + z_.y_ * b.y_ + z_.z_ * b.z_ + z_.w_ * b.w_;
        v.w_ = w_.x_ * b.x_ + w_.y_ * b.y_ + w_.z_ * b.z_ + w_.w_ * b.w_;
        return v;
    }
    

    ///
    /// 行列掛け算
    Mtx44& operator *= (const Mtx44& b) {
        Mtx44 m = *this * b;
        return (*this = m);
    }

    ///
    /// 転置行列化
    void transpose() {
        *this = getTransposed(*this);
    }
    
    ///
    /// 転置行列生成
    Mtx44 getTransposed(Mtx44& mtx) const {
        Mtx44 m;
        m.x_.x_ = mtx.x_.x_; m.x_.y_ = mtx.y_.x_; m.x_.z_ = mtx.z_.x_; m.x_.w_ = mtx.w_.x_;
        m.y_.x_ = mtx.x_.y_; m.y_.y_ = mtx.y_.y_; m.y_.z_ = mtx.z_.y_; m.y_.w_ = mtx.w_.y_;
        m.z_.x_ = mtx.x_.z_; m.z_.y_ = mtx.y_.z_; m.z_.z_ = mtx.z_.z_; m.z_.w_ = mtx.w_.z_;
        m.w_.x_ = mtx.x_.w_; m.w_.y_ = mtx.y_.w_; m.w_.z_ = mtx.z_.w_; m.w_.w_ = mtx.w_.w_;
        return m;
    }
    


    ///
    /// ポインタ取得
    float* pointer() {
        return &x_.x_;
    }
    
    ///
    /// ポインタ取得
    const float* pointer() const {
        return &x_.x_;
    }
    
    ///
    /// 単位行列生成
    void identity() {
        x_ = Vec4(1,0,0,0);
        y_ = Vec4(0,1,0,0);
        z_ = Vec4(0,0,1,0);
        w_ = Vec4(0,0,0,1);
    }
    
    ///
    ///
    static Mtx44 getIdentity() {
        return Mtx44();
    }
    
    ///
    /// 並行移動行列生成
    void translate(const Position3D& v) {
        makeTranslate(*this, v.x_, v.y_, v.z_);
    }
    
    ///
    /// 並行移動行列生成
    void translate(
        float x, 
        float y, 
        float z 
    ) {
        makeTranslate(*this, x, y, z);
    }
    
    ///
    /// 平行移動行列生成
    static Mtx44 getTranslate(
        float x, 
        float y, 
        float z
    ) {
        Mtx44 m;
        makeTranslate(m, x, y, z);
        return m;
    }
    
    ///
    /// 平行移動行列生成
    static void makeTranslate(
        Mtx44& mtx,
        float x,
        float y,
        float z
    ) {
        mtx.x_.x_ = 1; mtx.x_.y_ = 0; mtx.x_.z_ = 0; mtx.x_.w_ = 0;
        mtx.y_.x_ = 0; mtx.y_.y_ = 1; mtx.y_.z_ = 0; mtx.y_.w_ = 0;
        mtx.z_.x_ = 0; mtx.z_.y_ = 0; mtx.z_.z_ = 1; mtx.z_.w_ = 0;
        mtx.w_.x_ = x; mtx.w_.y_ = y; mtx.w_.z_ = z; mtx.w_.w_ = 1;
    }
    
    ///
    /// 平行移動成分設定
    void position(
        float x,
        float y,
        float z
    ) {
        w_.x_ = x;
        w_.y_ = y;
        w_.z_ = z;
    }
    
    ///
    /// 平行移動成分取得
    Position3D position() const {
        return Position3D(w_.x_, w_.y_, w_.z_);
    }
    
    ///
    /// スケール行列生成
    void scale(float s) {
        makeScale(*this, s, s, s);
    }
    
    ///
    /// スケール行列生成
    void scale(const Scale3D& v) {
        makeScale(*this, v.x_, v.y_, v.z_);
    }
    
    ///
    /// スケール行列生成
    void scale(float x, float y, float z) {
        makeScale(*this, x, y, z);
    }
    
    ///
    /// スケール行列生成
    static Mtx44 getScale(float x, float y, float z) {
        Mtx44 m;
        makeScale( m, x, y, z );
        return m;
    }
    
    ///
    /// スケール行列生成
    static void makeScale(Mtx44& m, float x, float y, float z) {
        m.x_.x_ = x; m.x_.y_ = 0; m.x_.z_ = 0; m.x_.w_ = 0;
        m.y_.x_ = 0; m.y_.y_ = y; m.y_.z_ = 0; m.y_.w_ = 0;
        m.z_.x_ = 0; m.z_.y_ = 0; m.z_.z_ = z; m.z_.w_ = 0;
        m.w_.x_ = 0; m.w_.y_ = 0; m.w_.z_ = 0; m.w_.w_ = 1;
    }
    
    ///
    /// 回転行列生成
    void rotateX(Radian r) {
        makeRotateX(*this, r);
    }
    
    ///
    /// 回転行列生成
    void rotateY(Radian r) {
        makeRotateY(*this, r);
    }
    
    ///
    /// 回転行列生成
    void rotateZ(Radian r) {
        makeRotateZ(*this, r);
    }
    
    ///
    /// 回転行列生成
    void rotate(Rotation& v) {
        makeRotateYawPitchRoll(
			*this, 
			toRadian(v.y_), 
			toRadian(v.x_), 
			toRadian(v.z_)
		);
    }

    ///
    /// 回転行列生成
    void rotate(
        Radian x,
        Radian y,
        Radian z
    ) {
        makeRotateYawPitchRoll(*this, y, x, z);
    }
    
    
    ///
    /// 回転行列生成
    void rotate(const Quaternion& q) {
        makeRotateQuaternion(*this, q);
    }
    
    ///
    /// 回転行列生成
    static Mtx44 getRotate(
        const Quaternion& q
    ) {
        Mtx44 m;
        return makeRotateQuaternion(m, q);
    }

    ///
    /// 回転行列生成
    static Mtx44 getRotate(
        Radian x,
        Radian y,
        Radian z
    ) {
        Mtx44 m;
        return makeRotateYawPitchRoll(m, y, x, z);
    }

    ///
    /// 回転行列生成
    static Mtx44 getRotate(
        Degree x,
        Degree y,
        Degree z
    ) {
        return getRotate(toRadian(y), toRadian(x), toRadian(z));
    }


    ///
    /// 回転行列生成
    static Mtx44 getRotate(
        const Rotation& r
    ) {
        return getRotate(
            toRadian(r.x_), 
            toRadian(r.y_), 
            toRadian(r.z_)
        );
    }


    ///
    /// 回転行列生成
    static Mtx44 getRotateY(
        Radian radian
    ) {
        Mtx44 m;
        return makeRotateY(m, radian);
    }
    
    ///
    /// 回転行列生成
    static Mtx44 getRotateZ(
        Radian radian
    ) {
        Mtx44 m;
        return makeRotateZ(m, radian);
    }
    
    
    
    ///
    /// 回転行列生成
    static Mtx44& makeRotateX(
        Mtx44& m,
        Radian radian
    ) {
        float r = radian.angle();
        float sin = std::sinf(r);
        float cos = std::cosf(r);

        m.x_.x_ = 1.0f;  m.x_.y_ = 0.0f;  m.x_.z_ = 0.0f;  m.x_.w_ = 0.0f;
        m.y_.x_ = 0.0f;  m.y_.y_ = cos;   m.y_.z_ = -sin;  m.y_.w_ = 0.0f;
		m.z_.x_ = 0.0f;  m.z_.y_ = sin;   m.z_.z_ =  cos;  m.z_.w_ = 0.0f;
		m.w_.x_ = 0.0f;  m.w_.y_ = 0.0f;  m.w_.z_ = 0.0f;  m.w_.w_ = 1.0f;
        return m;
    }
    
			 
	///
    /// 回転行列生成
    static Mtx44& makeRotateY(
        Mtx44& m,
        Radian radian
    ) {
        float r = radian.angle();
        float sin = std::sinf(r);
        float cos = std::cosf(r);
    
        m.x_.x_ =  cos;  m.x_.y_ = 0.0f;  m.x_.z_ =  sin;  m.x_.w_ = 0.0f;
        m.y_.x_ = 0.0f;  m.y_.y_ = 1.0f;  m.y_.z_ = 0.0f;  m.y_.w_ = 0.0f;
        m.z_.x_ = -sin;  m.z_.y_ = 0.0f;  m.z_.z_ =  cos;  m.z_.w_ = 0.0f;
		m.w_.x_ = 0.0f;  m.w_.y_ = 0.0f;  m.w_.z_ = 0.0f;  m.w_.w_ = 1.0f;
	
        return m;
    }
	
    ///
    ///
    static Mtx44& makeRotateZ(
        Mtx44& m,
        Radian radian
    ) {
        float r = radian.angle();
        float sin = std::sinf(r);
        float cos = std::cosf(r);
        
        m.x_.x_ =  cos;  m.x_.y_ =  sin;  m.x_.z_ = 0.0f;  m.x_.w_ = 0.0f;
        m.y_.x_ = -sin;  m.y_.y_ =  cos;  m.y_.z_ = 0.0f;  m.y_.w_ = 0.0f;
        m.z_.x_ = 0.0f;  m.z_.y_ = 0.0f;  m.z_.z_ = 1.0f;  m.z_.w_ = 0.0f;
        m.w_.x_ = 0.0f;  m.w_.y_ = 0.0f;  m.w_.z_ = 0.0f;  m.w_.w_ = 1.0f;
    
        return m;
    }


    ///
    /// 回転行列生成
    static Mtx44& makeRotateYawPitchRoll(
        Mtx44& m,
        Radian yaw,
        Radian pitch,
        Radian roll
    ) {
        Mtx44 yaw_mtx;
        makeRotateY(yaw_mtx, yaw);
        
        Mtx44 pitch_mtx;
        makeRotateX(pitch_mtx, pitch);
        
        Mtx44 roll_mtx;
        makeRotateZ(roll_mtx, roll);
        
        m = yaw_mtx * pitch_mtx * roll_mtx;

        return m;
    }
    
    ///
    /// 回転行列生成
    static Mtx44& makeRotateQuaternion(
        Mtx44& out,
        const Quaternion& quat
    ) {
    
        const float s = 2;
        float xs, ys, zs;
        float wx, wy, wz;
        float xx, xy, xz;
        float yy, yz, zz;


        float xang = quat.x_;
        float yang = quat.y_;
        float zang = quat.z_;
        float wang = quat.w_;


        xs = xang * s;  ys = yang * s;  zs = zang * s;
        wx = wang * xs; wy = wang * ys; wz = wang * zs;
        xx = xang * xs; xy = xang * ys; xz = xang * zs;
        yy = yang * ys; yz = yang * zs; zz = zang * zs;
        
        out.x_.x_ = float(1) - (yy + zz);
        out.x_.y_ = xy + wz;
        out.x_.z_ = xz - wy;
        out.x_.w_ = 0;

        out.y_.x_ = xy - wz;
        out.y_.y_ = float(1) - (xx + zz);
        out.y_.z_ = yz + wx;
        out.y_.w_ = 0;

        out.z_.x_ = xz + wy;
        out.z_.y_ = yz - wx;
        out.z_.z_ = float(1) - (xx + yy);
        out.z_.w_ = 0;
        
        out.w_.x_ = 0;
        out.w_.y_ = 0;
        out.w_.z_ = 0;
        out.w_.w_ = float(1);
    
        return out;
    }
    
    
    ///
    /// 任意軸回転行列生成
    static Mtx44& makeRotateAxis(
        Mtx44& out,
        const Vec3& axis,
        Radian radian
    ) {
		float r = radian.angle();
        float s = ::std::sinf(r);
        float c = ::std::cosf(r);
        float t = 1.0f - c;

        Vec3 vN = axis.getNormalized();

        float x = vN.x_;
        float y = vN.y_;
        float z = vN.z_;

        float xSq = x * x;
        float ySq = y * y;
        float zSq = z * z;

        out.x_.x_ = ( t * xSq )   + ( c );
        out.x_.y_ = ( t * x * y ) - ( s * z );
        out.x_.z_ = ( t * x * z ) + ( s * y );
        out.x_.w_ = 0.0f;

        out.y_.x_ = ( t * x * y ) + ( s * z );
        out.y_.y_ = ( t * ySq )   + ( c );
        out.y_.z_ = ( t * y * z ) - ( s * x );
        out.y_.w_ = 0.0f;

        out.z_.x_ = ( t * x * z ) - ( s * y );
        out.z_.y_ = ( t * y * z ) + ( s * x );
        out.z_.z_ = ( t * zSq )   + ( c );
        out.z_.w_ = 0.0f;
    
        out.w_.x_ = 0.0f;
        out.w_.y_ = 0.0f;
        out.w_.z_ = 0.0f;
        out.w_.w_ = 1.0f;

        return out;
    }
    
    
    ///
    /// 正射影行列生成
    void ortho(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) {
        makeOrtho(*this, left, right, bottom, top, near, far);
    }
    
    ///
    /// 正射影行列生成
    static Mtx44& makeOrtho(
        Mtx44& mtx,
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) {
        float a = 2.0f / (right - left);
        float b = 2.0f / (top - bottom);
        float c = -2.0f / (far - near);
        float tx = -(right + left) / (right - left);
        float ty = -(top + bottom) / (top - bottom);
        float tz = -(far + near) / (far - near);
        
        mtx.x_.x_ = a; mtx.x_.y_ = 0; mtx.x_.z_ = 0; mtx.x_.w_ = 0;
        mtx.y_.x_ = 0; mtx.y_.y_ = b; mtx.y_.z_ = 0; mtx.y_.w_ = 0;
        mtx.z_.x_ = 0; mtx.z_.y_ = 0; mtx.z_.z_ = c; mtx.z_.w_ = 0;
        mtx.w_.x_ = tx; mtx.w_.y_ = ty; mtx.w_.z_ = tz; mtx.w_.w_ = 1;
        return mtx;
    }
    
    ///
    /// 正射影行列生成
    static Mtx44 getOrtho(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) {
        Mtx44 m;
        makeOrtho(m, left, right, bottom, top, near, far);
        return m;
    }
    
    
    ///
    /// 投影行列生成
    void perspective(
        Radian fov,
		float width,
		float height,
		float near,
		float far
    ) {
        makePerspective(*this, fov, width, height, near, far);
    }
    
    
    ///
    /// 投影行列生成
    static void makePerspective(
        Mtx44& mtx,
        Radian fov_radian,
		float width,
		float height,
		float near,
		float far
	) {

        //  mesa
	    float radians = fov_radian.angle() * 0.5f;
	    float deltaZ = far - near;
	    float sine = std::sin(radians);
	    float cotangent = std::cos(radians) / sine;

        mtx.identity();
        float aspect =  height / width;
	    mtx.x_.x_ = cotangent / aspect;
	    mtx.y_.y_ = cotangent;
	    mtx.z_.z_ = -(far + near) / deltaZ;
	    mtx.w_.w_ = 0.0f;

	    mtx.w_.z_ = -2.0f * near * far / deltaZ;
	    mtx.z_.w_ = -1.0f;

	}
    
    ///
    /// 投影行列生成
    static Mtx44 getPerspective(
        Radian fov,
		float width,
		float height,
		float near,
		float far
    ) {
        Mtx44 m;
        makePerspective(m, fov, width, height, near, far);
        return m;
    }
    
    static void makeShadowBias(
        Mtx44& m
    ) {
        m.x_.x_ = 0.5f; m.x_.y_ = 0;    m.x_.z_ = 0;    m.x_.w_ = 0;
        m.y_.x_ = 0;    m.y_.y_ = 0.5f; m.y_.z_ = 0;    m.y_.w_ = 0;
        m.z_.x_ = 0;    m.z_.y_ = 0;    m.z_.z_ = 0.5f; m.z_.w_ = 0;
        m.w_.x_ = 0.5f; m.w_.y_ = 0.5f; m.w_.z_ = 0.5f; m.w_.w_ = 1.0f;
    }
    
    ///
    /// フラスタム行列生成
    void frustum(float left, float right, float bottom, float top, float near, float far) {
        makeFrustum(*this, left, right, bottom, top, near, far);
    }
    
    
    ///
    /// フラスタム行列生成
    static void makeFrustum(
        Mtx44& mtx,
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) {
        float a = 2.0f * near / (right - left);
        float b = 2.0f * near / (top - bottom);
        float c = (right + left) / (right - left);
        float d = (top + bottom) / (top - bottom);
        float e = -(far + near) / (far - near);
        float f = -2.0f * far * near / (far - near);
      
        mtx.x_.x_ =    a; mtx.x_.y_ = 0.0f; mtx.x_.z_ = 0.0f; mtx.x_.w_ =  0.0f;
        mtx.y_.x_ = 0.0f; mtx.y_.y_ =    b; mtx.y_.z_ = 0.0f; mtx.y_.w_ =  0.0f;
        mtx.z_.x_ =    c; mtx.z_.y_ =    d; mtx.z_.z_ =    e; mtx.z_.w_ = -1.0f;
        mtx.w_.x_ = 0.0f; mtx.w_.y_ = 0.0f; mtx.w_.z_ =    f; mtx.w_.w_ =  0.0f;
    }
    
    ///
    /// フラスタム行列生成
    static Mtx44 getFrustum(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) {
        Mtx44 m;
        makeFrustum(m, left, right, bottom, top, near, far);
        return m;
    }


    ///
    /// 視線行列生成
    void lookat(
        const Vec3& eye,
        const Vec3& target,
        const Vec3& up
    ){
        makeLookAt(*this, eye, target, up);
    }
    
    ///
    /// 視線行列生成
    void lookat(
        const Vec3& eye,
        const Vec3& normalized_front,
        const Vec3& normalized_right,
        const Vec3& normalized_up
    ) {
        makeLookAt(*this, eye, normalized_front, normalized_right, normalized_up);
    }
    
    
    ///
    /// 視線行列生成
    static void makeLookAt(
        Mtx44& mtx,
        const Vec3& eye,
        const Vec3& target,
        const Vec3& up
    ){

        Vec3 normalized_front = (eye - target).getNormalized();
        Vec3 normalized_right = up.crossProduct(normalized_front).getNormalized();
        Vec3 normalized_up = normalized_front.crossProduct(normalized_right);
        makeLookAt(
            mtx, 
            eye, 
            normalized_front, 
            normalized_right, 
            normalized_up
        );

    }

    ///
    /// 視線行列生成
    static void makeLookAt(
        Mtx44& mtx,
        const Vec3& eye,
        const Vec3& normalized_front,
        const Vec3& normalized_right,
        const Vec3& normalized_up
    ){
        T3_ASSERT(normalized_front.isNormalized());
        T3_ASSERT(normalized_right.isNormalized());
        T3_ASSERT(normalized_up.isNormalized());

        mtx.x_ = Vec4(normalized_right, 0);
        
        mtx.y_ = Vec4(normalized_up, 0);
        
        mtx.z_ = Vec4(normalized_front, 0);
        
        mtx.w_ = Vec4(0, 0, 0, 1);
        
        Vec4 eye_prime = mtx * Vec4(-eye, 1);
        mtx.transpose();
        mtx.w_ = eye_prime;
    }

    
    ///
    /// 視線行列生成
    static Mtx44 getLookAt(
        const Vec3& eye,
        const Vec3& target,
        const Vec3& up
    ){
        Mtx44 m;
        makeLookAt( m, eye, target, up );
        return m;
    }
    
    

    ///
    /// 逆行列生成
    static bool makeInverse(
        Mtx44& dest,
        const Mtx44 src
    ) {
        const float* m1 = src.pointer();
        float* m2 = dest.pointer();
    
        int i;
        int j;
        int k;
        float lu[20];
        float* plu[4];
        float det;
  
        
        for (j = 0; j < 4; ++j) {
            float max = fabs(*(plu[j] = lu + 5 * j) = *(m1++));
            for (i = 0; ++i < 4;) {
                float a = fabs(plu[j][i] = *(m1++));

                if (a > max) max = a;

            }

            if (max == 0.0f) return false;

            plu[j][4] = 1.0f / max;
        }
  
        det = 1.0f;
  
        
        for (j = 0; j < 4; ++j) {
            float max = fabs(plu[j][j] * plu[j][4]);
            i = j;
            for (k = j; ++k < 4;) {
                float a = fabs(plu[k][j] * plu[k][4]);
                if (a > max) {
                    max = a;
                    i = k;
                }
            }
    
            if (i > j) {
                float *t = plu[j];
                plu[j] = plu[i];
                plu[i] = t;
                det = -det;
            }
            if (plu[j][j] == 0.0f) return false;
            det *= plu[j][j];
    
            for (k = j; ++k < 4;) {
                plu[k][j] /= plu[j][j];
                for (i = j; ++i < 4;) {
                    plu[k][i] -= plu[j][i] * plu[k][j];
                }
            }
        }
  
        
        for (k = 0; k < 4; ++k) {
        
            for (i = 0; i < 4; ++i) {
                m2[i * 4 + k] = (plu[i] == lu + k * 5) ? 1.0f : 0.0f;
            }
            
            for (i = 0; i < 4; ++i) {
                for (j = i; ++j < 4;) {
                    m2[j * 4 + k] -= m2[i * 4 + k] * plu[j][i];
                }
            }
            for (i = 4; --i >= 0;){
                for (j = i; ++j < 4;) {
                    m2[i * 4 + k] -= plu[i][j] * m2[j * 4 + k];
                }
                m2[i * 4 + k] /= plu[i][i];
            }
        }
  
        return true;
    }
    
public:
    
    Vec4 x_; ///< 1要素
    Vec4 y_; ///< 2要素
    Vec4 z_; ///< 3要素
    Vec4 w_; ///< 4要素
};



TRI_CORE_NS_END



#endif // TRI_MATRIX_HPP_INCLUDED

