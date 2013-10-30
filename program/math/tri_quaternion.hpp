

#ifndef TRI_QUATERNION_HPP_INCLUDED
#define TRI_QUATERNION_HPP_INCLUDED

#include "tri_matrix.hpp"
#include "../math/tri_math_define.hpp"
#include "../math/tri_math_util.hpp"
#include "../util/tri_equal_comparable.hpp"

namespace t3 {
inline namespace math {

template <typename T>
struct QuaternionTemplate
    : public EqalComparable< QuaternionTemplate<T> >
{
    
    T x;
    T y;
    T z;
    T w;
    
    //  ctor
    QuaternionTemplate()
        : x(0)
        , y(0)
        , z(0)
        , w(1)
    {}
        
    QuaternionTemplate( T x, T y, T z, T w )
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}
    
    QuaternionTemplate( const QuaternionTemplate<T>& q )
        : x(q.x)
        , y(q.y)
        , z(q.z)
        , w(q.w)
    {}
    
    //  slerp
    QuaternionTemplate<T> slerp( T t, const QuaternionTemplate<T>& v1 ) const{
        T dot = dotProduct( v1 );
        if ( dot > 1 - EPSILON ){
            QuaternionTemplate<T> result = v1 + (*this - v1).getScaledQuaternion(t);
        }
        
        t3::clampLimitation( dot, 0.0f, 1.0f );
        
        T theta0 = acosf( dot );
        T theta = theta0 * t;
        
        QuaternionTemplate<T> v2 = (v1 - getScaledQuaternion(dot));
        v2.normalize();
        
        QuaternionTemplate<T> q = getScaledQuaternion( cosf(theta) ) + v2.getScaledQuaternion( sin(theta) );
        q.normalize();
        
        return q;
    };
    
    //  回転させる
    QuaternionTemplate<T> getRotatedQuaternion( const QuaternionTemplate<T>& b ) const{
        QuaternionTemplate<T> q;
        q.w = w * b.w - x * b.x - y * b.y - z * b.z;
        q.x = w * b.x + x * b.w + y * b.z - z * b.y;
        q.y = w * b.y + y * b.w + z * b.x - x * b.z;
        q.z = w * b.z + z * b.w + x * b.y - y * b.x;
        q.normalize();
        return q;        
    }
    
    //  拡縮させる
    QuaternionTemplate<T> getScaledQuaternion( T s ) const {
        return QuaternionTemplate<T>( x * s, y * s, z * s, w * s );
    }
    
    //  内積
    T dotProduct( const QuaternionTemplate<T>& q ) const {
        return x * q.x + y * q.y + z * q.z + w * q.w;
    }
    
    //  行列に変換
    Mtx3Template<T> toMatrix() const {
        const T s = 2;
        T xs, ys, zs;
        T wx, wy, wz;
        T xx, xy, xz;
        T yy, yz, zz;
        xs = x * s;  ys = y * s;  zs = z * s;
        wx = w * xs; wy = w * ys; wz = w * zs;
        xx = x * xs; xy = x * ys; xz = x * zs;
        yy = y * ys; yz = y * zs; zz = z * zs;
        
        Mtx3Template<T> m;
        m.x.x = 1 - (yy + zz); m.y.x = xy - wz;  m.z.x = xz + wy;
        m.x.y = xy + wz; m.y.y = 1 - (xx + zz); m.z.y = yz - wx;
        m.x.z = xz - wy; m.y.z = yz + wx;  m.z.z = 1 - (xx + yy);
        return m;
    }

    //  ベクトルに変換
    Vec4Template<T> toVec4() const {
        return Vec4Template<T>( x, y, z, w );
    }
    
    //  QuaternionTemplate - QuaternionTemplate
    QuaternionTemplate<T> operator-( const QuaternionTemplate<T>& q ) const {
        return QuaternionTemplate<T>( x - q.x, y - q.y, z - q.z, w - q.w );
    }
    
    //  QuaternionTemplate + QuaternionTemplate
    QuaternionTemplate<T> operator+( const QuaternionTemplate<T>& q ) const {
        return QuaternionTemplate<T>( x + q.x, y + q.y, z + q.z, w + q.w );
    }
    
    //  QuaternionTemplate == QuaternionTemplate
    bool operator==( const QuaternionTemplate<T>& q ) const {
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
    void rotate( const QuaternionTemplate<T>& q2 ){
        QuaternionTemplate<T> q;
    
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
    
    static QuaternionTemplate<T> createFromVectors( 
        const Vec3Template<T>& v0,
        const Vec3Template<T>& v1
    ){
    
        if ( v0 == -v1 ){
            return QuaternionTemplate<T>::createFromAxisAngle( Vec3(1, 0, 0), PI );
        }
        Vec3Template<T> c = v0.crossProduct( v1 );
        T d = v0.dotProduct( v1 );
        T s = sqrtf((1 + d) * 2);

        QuaternionTemplate<T> q;
        q.x = c.x / s;
        q.y = c.y / s;
        q.z = c.z / s;
        q.w = s / 2.0f;
        return q;
    }
    
    //  軸回転値からクォータニオンを生成
    static QuaternionTemplate<T> createFromAxisAngle(
        const Vec3Template<T>& axis, 
        float radians
    ){
        QuaternionTemplate<T> q;
        q.w = cosf( radians / 2.0f );
        q.x = q.y = q.z = sinf( radians / 2.0f );
        q.x *= axis.x;
        q.y *= axis.y;
        q.z *= axis.z;
        return q;
    }

};

//  typedef
typedef QuaternionTemplate<float> Quaternion;


} // namespace math
} // namespace t3

#endif // TRI_QUATERNION_HPP_INCLUDED










