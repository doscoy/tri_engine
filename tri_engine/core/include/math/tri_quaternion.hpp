/**
    @file tri_quaternion.hpp
    クォータニオン.
*/

#ifndef TRI_QUATERNION_HPP_INCLUDED
#define TRI_QUATERNION_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "../math/tri_math_define.hpp"
#include "../math/tri_math_util.hpp"

TRI_CORE_NS_BEGIN


///
/// クォータニオン
template <typename T>
struct QuaternionTemplate
{
    
    T x_;
    T y_;
    T z_;
    T w_;
    
    ///
    /// コンストラクタ
    QuaternionTemplate()
        : x_(0)
        , y_(0)
        , z_(0)
        , w_(1)
    {}
        
    ///
    /// コンストラクタ
    QuaternionTemplate(T ax, T ay, T az, T aw)
        : x_(ax)
        , y_(ay)
        , z_(az)
        , w_(aw)
    {}
    
    ///
    /// コンストラクタ
    QuaternionTemplate(const QuaternionTemplate<T>& q)
        : x_(q.x_)
        , y_(q.y_)
        , z_(q.z_)
        , w_(q.w_)
    {}
    
    ///
    /// コンストラクタ
    QuaternionTemplate(
        const Vec3& axis,
        const float degree
    ) {
        set(axis, degree);
    }
    
    
    ///
    /// 値設定
    void set(
        const Vec3Template<T>& axis,
        const float degree
    ) {
        makeFromAxisAngle(*this, axis, toRadian(degree));
    }
    
    
    
    ///
    /// slerp
    QuaternionTemplate<T> slerp(T t, const QuaternionTemplate<T>& v1) const{
        T dot = dotProduct(v1);
        if (dot > 1 - EPSILON) {
            QuaternionTemplate<T> result = v1 + (*this - v1).getScaledQuaternion(t);
        }
        
        t3::clampLimitation(dot, 0.0f, 1.0f);
        
        T theta0 = acosf(dot);
        T theta = theta0 * t;
        
        QuaternionTemplate<T> v2 = (v1 - getScaledQuaternion(dot));
        v2.normalize();
        
        QuaternionTemplate<T> q = getScaledQuaternion(cosf(theta)) + v2.getScaledQuaternion(sin(theta));
        q.normalize();
        
        return q;
    };
    
    ///
    /// 回転させる
    QuaternionTemplate<T> getRotatedQuaternion(const QuaternionTemplate<T>& b) const{
        QuaternionTemplate<T> q;
        q.w_ = w_ * b.w_ - x_ * b.x_ - y_ * b.y_ - z_ * b.z_;
        q.x_ = w_ * b.x_ + x_ * b.w_ + y_ * b.z_ - z_ * b.y_;
        q.y_ = w_ * b.y_ + y_ * b.w_ + z_ * b.x_ - x_ * b.z_;
        q.z_ = w_ * b.z_ + z_ * b.w_ + x_ * b.y_ - y_ * b.x_;
        q.normalize();
        return q;        
    }
    
    ///
    /// 拡縮させる
    QuaternionTemplate<T> getScaledQuaternion(T s) const {
        return QuaternionTemplate<T>(x_ * s, y_ * s, z_ * s, w_ * s);
    }
    
    ///
    /// 内積
    T dotProduct(const QuaternionTemplate<T>& q) const {
        return x_ * q.x_ + y_ * q.y_ + z_ * q.z_ + w_ * q.w_;
    }
    
    ///
    /// QuaternionTemplate - QuaternionTemplate
    QuaternionTemplate<T> operator-(const QuaternionTemplate<T>& q) const {
        return QuaternionTemplate<T>( x_ - q.x_, y_ - q.y_, z_ - q.z_, w_ - q.w_);
    }
    
    ///
    /// QuaternionTemplate + QuaternionTemplate
    QuaternionTemplate<T> operator+(const QuaternionTemplate<T>& q) const {
        return QuaternionTemplate<T>(x_ + q.x_, y_ + q.y_, z_ + q.z_, w_ + q.w_);
    }
    

    ///
    /// 回転
    void makeRotate(
        QuaternionTemplate<T>& dest,
        const QuaternionTemplate<T>& lhs,
        const QuaternionTemplate<T>& rhs
    ) {
        dest.w_ = lhs.w_ * rhs.w_ - lhs.x_ * rhs.x_ - lhs.y_ * rhs.y_ - lhs.z_ * rhs.z_;
        dest.x_ = lhs.w_ * rhs.x_ + lhs.x_ * rhs.w_ + lhs.y_ * rhs.z_ - lhs.z_ * rhs.y_;
        dest.y_ = lhs.w_ * rhs.y_ - lhs.x_ * rhs.z_ + lhs.y_ * rhs.w_ + lhs.z_ * rhs.x_;
        dest.z_ = lhs.w_ * rhs.z_ + lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_ + lhs.z_ * rhs.w_;
        dest.normalize();
    }

    
    ///
    /// operator +=
    const QuaternionTemplate<T>& operator +=(
        const QuaternionTemplate<T>& rhs
    ) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        w_ += rhs.w_;
        
        return *this;
    }
    
    ///
    ///  QuaternionTemplate == QuaternionTemplate
    bool operator==(const QuaternionTemplate<T>& q) const {
        return x_ == q.x_ 
            && y_ == q.y_ 
            && z_ == q.z_ 
            && w_ == q.w_;
    }
    
    ///
    /// 正規化
    void normalize(){
        *this = getScaledQuaternion(1 / sqrtf( dotProduct(*this)));
    }
    
    ///
    /// 回転
    void rotate(const QuaternionTemplate<T>& r) {

        makeRotate(*this, r, *this);
    }
    
    ///
    /// dump
    void dump() const {
        std::cout << "x:" << x_ << " y:" << y_ << " z:" << z_ << " w:" << w_ << std::endl;
    }
    
    ///
    /// ２つのベクトル間を移動するクォータニオンを生成
    static QuaternionTemplate<T> makeFromVectors(
        const Vec3Template<T>& start,
        const Vec3Template<T>& goal
    ){
    
        QuaternionTemplate<T> q;
        if (start == -goal) {
            makeFromAxisAngle(
                q,
                Vec3(1, 0, 0),
                PI
            );
            return q;
        }
        Vec3Template<T> c = start.crossProduct(goal);
        T d = start.dotProduct(goal);
        T s = sqrtf((1 + d) * 2);


        q.x_ = c.x_ / s;
        q.y_ = c.y_ / s;
        q.z_ = c.z_ / s;
        q.w_ = s / 2.0f;
        return q;
    }
    
    ///
    /// 軸回転値からクォータニオンを生成
    static void makeFromAxisAngle(
        QuaternionTemplate<T>& q,
        const Vec3Template<T>& axis, 
        float angle
    ){
        float ang_div_2 = angle * 0.5f;
        q.w_ = cosf(ang_div_2);
        q.x_ = q.y_ = q.z_ = sinf(ang_div_2);
        q.x_ *= axis.x_;
        q.y_ *= axis.y_;
        q.z_ *= axis.z_;
    }
    
    ///
    /// オイラー角から生成
    static void makeFromEuler(
        QuaternionTemplate<T>& dest,
        Vec3Template<T> euler
    ) {
        makeQuaternionFromEuler(dest, euler.x_, euler.y_, euler.z_);
    }
    
    
    ///
    /// オイラー角から生成
    static void makeFromEuler(
        QuaternionTemplate<T>& dest,
        T x,
        T y,
        T z
    ) {

        float tmpx = x * 0.5f;
        float tmpy = y * 0.5f;
        float tmpz = z * 0.5f;

        float cr = std::cosf(tmpx);
        float cp = std::cosf(tmpy);
        float cy = std::cosf(tmpz);

        float sr = std::sinf(tmpx);
        float sp = std::sinf(tmpy);
        float sy = std::sinf(tmpz);

        float cpcy = cp * cy;
        float spsy = sp * sy;
        float cpsy = cp * sy;
        float spcy = sp * cy;

        dest.w_ = cr * cpcy + sr * spsy;
        dest.x_ = sr * cpcy - cr * spsy;
        dest.y_ = cr * spcy + sr * cpsy;
        dest.z_ = cr * cpsy - sr * spcy;
    }

};

//  typedef
typedef QuaternionTemplate<float> Quaternion;


TRI_CORE_NS_END

#endif // TRI_QUATERNION_HPP_INCLUDED










