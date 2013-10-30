

#ifndef TRI_QUATERNION_HPP_INCLUDED
#define TRI_QUATERNION_HPP_INCLUDED

#include "tri_matrix.hpp"
#include "../math/tri_math_define.hpp"
#include "../math/tri_math_util.hpp"
#include "../util/tri_equal_comparable.hpp"

namespace t3 {
inline namespace math {

template <typename T>
struct Quaternion
    : public EqalComparable< Quaternion<T> >
{
    
    T x;
    T y;
    T z;
    T w;
    
    //  ctor
    Quaternion()
        : x(0)
        , y(0)
        , z(0)
        , w(1)
    {}
        
    Quaternion( T x, T y, T z, T w )
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}
    
    Quaternion( const Quaternion<T>& q )
        : x(q.x)
        , y(q.y)
        , z(q.z)
        , w(q.w)
    {}
    
    //  slerp
    Quaternion<T> slerp( T t, const Quaternion<T>& v1 ) const{
        T dot = dotProduct( v1 );
        if ( dot > 1 - EPSILON ){
            Quaternion<T> result = v1 + (*this - v1).getScaledQuaternion(t);
        }
        
        t3::clampLimitation( dot, 0.0f, 1.0f );
        
        T theta0 = acosf( dot );
        T theta = theta0 * t;
        
        Quaternion<T> v2 = (v1 - getScaledQuaternion(dot));
        v2.normalize();
        
        Quaternion<T> q = getScaledQuaternion( cosf(theta) ) + v2.getScaledQuaternion( sin(theta) );
        q.normalize();
        
        return q;
    };
    
    //  回転させる
    Quaternion<T> getRotatedQuaternion( const Quaternion<T>& b ) const{
        Quaternion<T> q;
        q.w = w * b.w - x * b.x - y * b.y - z * b.z;
        q.x = w * b.x + x * b.w + y * b.z - z * b.y;
        q.y = w * b.y + y * b.w + z * b.x - x * b.z;
        q.z = w * b.z + z * b.w + x * b.y - y * b.x;
        q.normalize();
        return q;        
    }
    
    //  拡縮させる
    Quaternion<T> getScaledQuaternion( T s ) const {
        return Quaternion<T>( x * s, y * s, z * s, w * s );
    }
    
    //  内積
    T dotProduct( const Quaternion<T>& q ) const {
        return x * q.x + y * q.y + z * q.z + w * q.w;
    }
    
    //  行列に変換
    Matrix3<T> toMatrix() const {
        const T s = 2;
        T xs, ys, zs;
        T wx, wy, wz;
        T xx, xy, xz;
        T yy, yz, zz;
        xs = x * s;  ys = y * s;  zs = z * s;
        wx = w * xs; wy = w * ys; wz = w * zs;
        xx = x * xs; xy = x * ys; xz = x * zs;
        yy = y * ys; yz = y * zs; zz = z * zs;
        
        Matrix3<T> m;
        m.x.x = 1 - (yy + zz); m.y.x = xy - wz;  m.z.x = xz + wy;
        m.x.y = xy + wz; m.y.y = 1 - (xx + zz); m.z.y = yz - wx;
        m.x.z = xz - wy; m.y.z = yz + wx;  m.z.z = 1 - (xx + yy);
        return m;
    }

    //  ベクトルに変換
    Vec4<T> toVec4() const {
        return Vec4<T>( x, y, z, w );
    }
    
    //  Quaternion - Quaternion
    Quaternion<T> operator-( const Quaternion<T>& q ) const {
        return Quaternion<T>( x - q.x, y - q.y, z - q.z, w - q.w );
    }
    
    //  Quaternion + Quaternion
    Quaternion<T> operator+( const Quaternion<T>& q ) const {
        return Quaternion<T>( x + q.x, y + q.y, z + q.z, w + q.w );
    }
    
    //  Quaternion == Quaternion
    bool operator==( const Quaternion<T>& q ) const {
        return x == q.x 
            && y == q.y 
            && z == q.z 
            && w == q.w;
    }
    
    //  正規化
    void normalize(){
        *this = getScaledQuaternion( 1 / sqrtf( dotProduct( *this ) ) );
    }
    
    //  回転
    void rotate( const Quaternion<T>& q2 ){
        Quaternion<T> q;
    
        q.w = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
        q.x = w * q2.x + x * q2.w + y * q2.z - z * q2.y;
        q.y = w * q2.y + y * q2.w + z * q2.x - x * q2.z;
        q.z = w * q2.z + z * q2.w + x * q2.y - y * q2.x;
    
        q.normalize();
        *this = q;
    }
    
    //  dump
    void dump() const {
        std::cout << "x:" << x << " y:" << y << " z:" << z << " w:" << w << std::endl;
    }
    
    static Quaternion<T> createFromVectors( 
        const Vec3<T>& v0,
        const Vec3<T>& v1
    ){
    
        if ( v0 == -v1 ){
            return Quaternion<T>::createFromAxisAngle( vec3_t(1, 0, 0), PI );
        }
        Vec3<T> c = v0.crossProduct( v1 );
        T d = v0.dotProduct( v1 );
        T s = sqrtf((1 + d) * 2);

        Quaternion<T> q;
        q.x = c.x / s;
        q.y = c.y / s;
        q.z = c.z / s;
        q.w = s / 2.0f;
        return q;
    }
    
    //  軸回転値からクォータニオンを生成
    static Quaternion<T> createFromAxisAngle(
        const Vec3<T>& axis, 
        float radians
    ){
        Quaternion<T> q;
        q.w = cosf( radians / 2.0f );
        q.x = q.y = q.z = sinf( radians / 2.0f );
        q.x *= axis.x;
        q.y *= axis.y;
        q.z *= axis.z;
        return q;
    }

};

//  typedef
typedef Quaternion<float> quat_t;


} // namespace math
} // namespace t3

#endif // TRI_QUATERNION_HPP_INCLUDED










