

#ifndef TRI_MATRIX_HPP_INCLUDED
#define TRI_MATRIX_HPP_INCLUDED

//  include
#include "tri_vec2.hpp"
#include "tri_vec3.hpp"
#include "tri_vec4.hpp"
#include "../math/tri_math_util.hpp"


namespace t3 {

// Matrix2
template <typename T>
struct Matrix2 {
    Matrix2()
    {
        x.x = 1; x.y = 0;
        y.x = 0; y.y = 1;
    }
    Matrix2(const T* m)
    {
        x.x = m[0]; x.y = m[1];
        y.x = m[2]; y.y = m[3];
    }
    Vec2<T> x;
    Vec2<T> y;
};


template <typename T>
struct Matrix3 {
    Matrix3()
    {
        x.x = 1; x.y = 0; x.z = 0;
        y.x = 0; y.y = 1; y.z = 0;
        z.x = 0; z.y = 0; z.z = 1;
    }
    Matrix3(const T* m)
    {
        x.x = m[0]; x.y = m[1]; x.z = m[2];
        y.x = m[3]; y.y = m[4]; y.z = m[5];
        z.x = m[6]; z.y = m[7]; z.z = m[8];
    }
    Matrix3(vec3_t x, vec3_t y, vec3_t z) : x(x), y(y), z(z)
    {
    }
    Matrix3 transposed() const
    {
        Matrix3 m;
        m.x.x = x.x; m.x.y = y.x; m.x.z = z.x;
        m.y.x = x.y; m.y.y = y.y; m.y.z = z.y;
        m.z.x = x.z; m.z.y = y.z; m.z.z = z.z;
        return m;
    }
    const T* Pointer() const
    {
        return &x.x;
    }
    Vec3<T> x;
    Vec3<T> y;
    Vec3<T> z;
};

template <typename T>
struct Matrix4 {
    Matrix4()
    {
        x.x = 1; x.y = 0; x.z = 0; x.w = 0;
        y.x = 0; y.y = 1; y.z = 0; y.w = 0;
        z.x = 0; z.y = 0; z.z = 1; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    Matrix4(const Matrix3<T>& m)
    {
        x.x = m.x.x; x.y = m.x.y; x.z = m.x.z; x.w = 0;
        y.x = m.y.x; y.y = m.y.y; y.z = m.y.z; y.w = 0;
        z.x = m.z.x; z.y = m.z.y; z.z = m.z.z; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    Matrix4(const T* m)
    {
        x.x = m[0];  x.y = m[1];  x.z = m[2];  x.w = m[3];
        y.x = m[4];  y.y = m[5];  y.z = m[6];  y.w = m[7];
        z.x = m[8];  z.y = m[9];  z.z = m[10]; z.w = m[11];
        w.x = m[12]; w.y = m[13]; w.z = m[14]; w.w = m[15];
    }
    Matrix4 operator * (const Matrix4& b) const
    {
        Matrix4 m;
        m.x.x = x.x * b.x.x + x.y * b.y.x + x.z * b.z.x + x.w * b.w.x;
        m.x.y = x.x * b.x.y + x.y * b.y.y + x.z * b.z.y + x.w * b.w.y;
        m.x.z = x.x * b.x.z + x.y * b.y.z + x.z * b.z.z + x.w * b.w.z;
        m.x.w = x.x * b.x.w + x.y * b.y.w + x.z * b.z.w + x.w * b.w.w;
        m.y.x = y.x * b.x.x + y.y * b.y.x + y.z * b.z.x + y.w * b.w.x;
        m.y.y = y.x * b.x.y + y.y * b.y.y + y.z * b.z.y + y.w * b.w.y;
        m.y.z = y.x * b.x.z + y.y * b.y.z + y.z * b.z.z + y.w * b.w.z;
        m.y.w = y.x * b.x.w + y.y * b.y.w + y.z * b.z.w + y.w * b.w.w;
        m.z.x = z.x * b.x.x + z.y * b.y.x + z.z * b.z.x + z.w * b.w.x;
        m.z.y = z.x * b.x.y + z.y * b.y.y + z.z * b.z.y + z.w * b.w.y;
        m.z.z = z.x * b.x.z + z.y * b.y.z + z.z * b.z.z + z.w * b.w.z;
        m.z.w = z.x * b.x.w + z.y * b.y.w + z.z * b.z.w + z.w * b.w.w;
        m.w.x = w.x * b.x.x + w.y * b.y.x + w.z * b.z.x + w.w * b.w.x;
        m.w.y = w.x * b.x.y + w.y * b.y.y + w.z * b.z.y + w.w * b.w.y;
        m.w.z = w.x * b.x.z + w.y * b.y.z + w.z * b.z.z + w.w * b.w.z;
        m.w.w = w.x * b.x.w + w.y * b.y.w + w.z * b.z.w + w.w * b.w.w;
        return m;
    }

    Vec4<T> operator * (const Vec4<T>& b) const // 検証未了
    {
        Vec4<T> v;
        v.x = x.x * b.x + x.y * b.y + x.z * b.z + x.w * b.w;
        v.y = y.x * b.x + y.y * b.y + y.z * b.z + y.w * b.w;
        v.z = z.x * b.x + z.y * b.y + z.z * b.z + z.w * b.w;
        v.w = w.x * b.x + w.y * b.y + w.z * b.z + w.w * b.w;
        return v;
    }
 
    Matrix4& operator *= (const Matrix4& b)
    {
        Matrix4 m = *this * b;
        return (*this = m);
    }
    Matrix4 transposed() const
    {
        Matrix4 m;
        m.x.x = x.x; m.x.y = y.x; m.x.z = z.x; m.x.w = w.x;
        m.y.x = x.y; m.y.y = y.y; m.y.z = z.y; m.y.w = w.y;
        m.z.x = x.z; m.z.y = y.z; m.z.z = z.z; m.z.w = w.z;
        m.w.x = x.w; m.w.y = y.w; m.w.z = z.w; m.w.w = w.w;
        return m;
    }
    Matrix3<T> toMat3() const
    {
        Matrix3<T> m;
        m.x.x = x.x; m.y.x = y.x; m.z.x = z.x;
        m.x.y = x.y; m.y.y = y.y; m.z.y = z.y;
        m.x.z = x.z; m.y.z = y.z; m.z.z = z.z;
        return m;
    }
    const T* pointer() const
    {
        return &x.x;
    }
    static Matrix4<T> identity()
    {
        return Matrix4();
    }
    
    void translate(const Vec3<T>& v)
    {
        makeTranslateMatrix( *this, v.x, v.y, v.z );
    }
    
    void translate( T x, T y, T z )
    {
        makeTranslateMatrix( *this, x, y, z );
    }
    
    static Matrix4<T> getTranslateMatrix( T x, T y, T z)
    {
        Matrix4 m;
        makeTranslateMatrix( m, x, y, z );
        return m;
    }
    
    static void makeTranslateMatrix( Matrix4<T>& mtx, T x, T y, T z)
    {
        mtx.x.x = 1; mtx.x.y = 0; mtx.x.z = 0; mtx.x.w = 0;
        mtx.y.x = 0; mtx.y.y = 1; mtx.y.z = 0; mtx.y.w = 0;
        mtx.z.x = 0; mtx.z.y = 0; mtx.z.z = 1; mtx.z.w = 0;
        mtx.w.x = x; mtx.w.y = y; mtx.w.z = z; mtx.w.w = 1;
    }
    
    void scale( T s )
    {
        makeScaleMatrix( *this, s, s, s );
    }
    
    void scale( const Vec3<T> v )
    {
        makeScaleMatrix( *this, v.x, v.y, v.z );
    }
    
    void scale( T x, T y, T z )
    {
        makeScaleMatrix( *this, x, y, z );
    }
    
    static Matrix4<T> getScaleMatrix( T x, T y, T z )
    {
        Matrix4 m;
        makeScaleMatrix( m, x, y, z );
        return m;
    }
    
    static void makeScaleMatrix( Matrix4<T>& m, T x, T y, T z)
    {
        m.x.x = x; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = y; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = z; m.z.w = 0;
        m.w.x = 0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
    }
    
    
    
    static Matrix4<T> rotate(T degrees)
    {
        T radians = t3::toRadian( degrees );
        T s = t3::sinf(radians);
        T c = t3::cosf(radians);
        
        Matrix4 m;
        m.x.x =  c; m.x.y = s; m.x.z = 0; m.x.w = 0;
        m.y.x = -s; m.y.y = c; m.y.z = 0; m.y.w = 0;
        m.z.x =  0; m.z.y = 0; m.z.z = 1; m.z.w = 0;
        m.w.x =  0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        
        return m;
    }
    
    void ortho( T left, T right, T bottom, T top, T near, T far ){
        makeOrthoMatrix( *this, left, right, bottom, top, near, far );
    }
    
    static void makeOrthoMatrix( Matrix4<T>& mtx, T left, T right, T bottom, T top, T near, T far)
    {
        T a = 2.0f / (right - left);
        T b = 2.0f / (top - bottom);
        T c = -2.0f / (far - near);
        T tx = -(right + left) / (right - left);
        T ty = -(top + bottom) / (top - bottom);
        T tz = -(far + near) / (far - near);
        
        mtx.x.x = a; mtx.x.y = 0; mtx.x.z = 0; mtx.x.w = 0;
        mtx.y.x = 0; mtx.y.y = b; mtx.y.z = 0; mtx.y.w = 0;
        mtx.z.x = 0; mtx.z.y = 0; mtx.z.z = c; mtx.z.w = 0;
        mtx.w.x = tx; mtx.w.y = ty; mtx.w.z = tz; mtx.w.w = 1;
    }
    static Matrix4<T> getOrthoMatrix(T left, T right, T bottom, T top, T near, T far)
    {
        Matrix4 m;
        makeOrthoMatrix( m, left, right, bottom, top, near, far );
        return m;
    }
    
    void frustum( T left, T right, T bottom, T top, T near, T far ){
        makeFrustumMatrix( *this, left, right, bottom, top, near, far );
    }
    
    
    static void makeFrustumMatrix( Matrix4<T>& mtx, T left, T right, T bottom, T top, T near, T far )
    {
        T a = 2 * near / (right - left);
        T b = 2 * near / (top - bottom);
        T c = (right + left) / (right - left);
        T d = (top + bottom) / (top - bottom);
        T e = - (far + near) / (far - near);
        T f = -2 * far * near / (far - near);
      
        mtx.x.x = a; mtx.x.y = 0; mtx.x.z = 0; mtx.x.w = 0;
        mtx.y.x = 0; mtx.y.y = b; mtx.y.z = 0; mtx.y.w = 0;
        mtx.z.x = c; mtx.z.y = d; mtx.z.z = e; mtx.z.w = -1;
        mtx.w.x = 0; mtx.w.y = 0; mtx.w.z = f; mtx.w.w = 0;
    }
    
    static Matrix4<T> getFrustumMatrix( T left, T right, T bottom, T top, T near, T far )
    {
        Matrix4 m;
        makeFrustumMatrix( m, left, right, bottom, top, near, far );
        return m;
    }


    void lookat(
        const Vec3<T>& eye,
        const Vec3<T>& target,
        const Vec3<T>& up
    ){
        makeLookAtMatrix( *this, eye, target, up );
    }
    
    static void makeLookAtMatrix(
        Matrix4<T>& mtx,
        const Vec3<T>& eye,
        const Vec3<T>& target,
        const Vec3<T>& up
    ){
        Vec3<T> z = (eye - target).getNormalized();
        Vec3<T> x = up.crossProduct(z).getNormalized();
        Vec3<T> y = z.crossProduct(x).getNormalized();
        
        
        mtx.x = Vec4<T>(x.x, x.y, x.z, 0);
        mtx.y = Vec4<T>(y.x, y.y, y.z, 0);
        mtx.z = Vec4<T>(z.x, z.y, z.z, 0);
        mtx.w = Vec4<T>(0, 0, 0, 1);
        
        Vec4<T> eyePrime = mtx * Vec4<T>(-eye.x, -eye.y, -eye.z, 1);
        mtx = mtx.transposed();
        mtx.w = eyePrime;        
    }
    
    static Matrix4<T> getLookAtMatrix( 
        const Vec3<T>& eye,
        const Vec3<T>& target,
        const Vec3<T>& up
    ){
        Matrix4 m;
        makeLookAtMatrix( m, eye, target, up );
        return m;
    }
    
    Vec4<T> x;
    Vec4<T> y;
    Vec4<T> z;
    Vec4<T> w;
};


//  typedef
typedef Matrix2<float> mtx2_t;
typedef Matrix3<float> mtx3_t;
typedef Matrix4<float> mtx4_t;
    

}   // namespace t3

#endif // TRI_MATRIX_HPP_INCLUDED

