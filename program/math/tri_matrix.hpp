

#ifndef TRI_MATRIX_HPP_INCLUDED
#define TRI_MATRIX_HPP_INCLUDED

//  include
#include "tri_vec2.hpp"
#include "tri_vec3.hpp"
#include "tri_vec4.hpp"
#include "../math/tri_math_util.hpp"


namespace t3 {
inline namespace math {


// Mtx2Template
template <typename T>
struct Mtx2Template {
    Mtx2Template()
    {
        x_.x_ = 1; x_.y_ = 0;
        y_.x_ = 0; y_.y_ = 1;
    }
    Mtx2Template(const T* m)
    {
        x_.x_ = m[0]; x_.y_ = m[1];
        y_.x_ = m[2]; y_.y_ = m[3];
    }
    Vec2Template<T> x_;
    Vec2Template<T> y_;
};


template <typename T>
struct Mtx3Template {
    Mtx3Template()
    {
        x_.x_ = 1; x_.y_ = 0; x_.z_ = 0;
        y_.x_ = 0; y_.y_ = 1; y_.z_ = 0;
        z_.x_ = 0; z_.y_ = 0; z_.z_ = 1;
    }
    Mtx3Template(const T* m)
    {
        x_.x_ = m[0]; x_.y_ = m[1]; x_.z_ = m[2];
        y_.x_ = m[3]; y_.y_ = m[4]; y_.z_ = m[5];
        z_.x_ = m[6]; z_.y_ = m[7]; z_.z_ = m[8];
    }
    Mtx3Template(Vec3 x, Vec3 y, Vec3 z)
        : x_(x), y_(y), z_(z)
    {
    }
    Mtx3Template transposed() const
    {
        Mtx3Template m;
        m.x_.x_ = x_.x_; m.x_.y_ = y_.x_; m.x_.z_ = z_.x_;
        m.y_.x_ = x_.y_; m.y_.y_ = y_.y_; m.y_.z_ = z_.y_;
        m.z_.x_ = x_.z_; m.z_.y_ = y_.z_; m.z_.z_ = z_.z_;
        return m;
    }
    const T* Pointer() const
    {
        return &x_.x_;
    }
    Vec3Template<T> x_;
    Vec3Template<T> y_;
    Vec3Template<T> z_;
};

template <typename T>
struct Mtx4Template
{
    Mtx4Template()
    {
        identity();
    }
    Mtx4Template(const Mtx3Template<T>& m)
    {
        x_.x_ = m.x_.x_; x_.y_ = m.x_.y_; x_.z_ = m.x_.z_; x_.w_ = 0;
        y_.x_ = m.y_.x_; y_.y_ = m.y_.y_; y_.z_ = m.y_.z_; y_.w_ = 0;
        z_.x_ = m.z_.x_; z_.y_ = m.z_.y_; z_.z_ = m.z_.z_; z_.w_ = 0;
        w_.x_ = 0; w_.y_ = 0; w_.z_ = 0; w_.w_ = 1;
    }
    Mtx4Template(const T* m)
    {
        x_.x_ = m[0];  x_.y_ = m[1];  x_.z_ = m[2];  x_.w_ = m[3];
        y_.x_ = m[4];  y_.y_ = m[5];  y_.z_ = m[6];  y_.w_ = m[7];
        z_.x_ = m[8];  z_.y_ = m[9];  z_.z_ = m[10]; z_.w_ = m[11];
        w_.x_ = m[12]; w_.y_ = m[13]; w_.z_ = m[14]; w_.w_ = m[15];
    }
    
    
    
    
    Mtx4Template operator * (const Mtx4Template& rhs) const
    {
        return multiply(*this, rhs);
    }

    static Mtx4Template multiply(
        const Mtx4Template& lhs,
        const Mtx4Template& rhs
    ) {
        Mtx4Template m;
        m.x_.x_ = lhs.x_.x_ * rhs.x_.x_ + lhs.x_.y_ * rhs.y_.x_ + lhs.x_.z_ * rhs.z_.x_ + lhs.x_.w_ * rhs.w_.x_;
        m.x_.y_ = lhs.x_.x_ * rhs.x_.y_ + lhs.x_.y_ * rhs.y_.y_ + lhs.x_.z_ * rhs.z_.y_ + lhs.x_.w_ * rhs.w_.y_;
        m.x_.z_ = lhs.x_.x_ * rhs.x_.z_ + lhs.x_.y_ * rhs.y_.z_ + lhs.x_.z_ * rhs.z_.z_ + lhs.x_.w_ * rhs.w_.z_;
        m.x_.w_ = lhs.x_.x_ * rhs.x_.w_ + lhs.x_.y_ * rhs.y_.w_ + lhs.x_.z_ * rhs.z_.w_ + lhs.x_.w_ * rhs.w_.w_;
        m.y_.x_ = lhs.y_.x_ * rhs.x_.x_ + lhs.y_.y_ * rhs.y_.x_ + lhs.y_.z_ * rhs.z_.x_ + lhs.y_.w_ * rhs.w_.x_;
        m.y_.y_ = lhs.y_.x_ * rhs.x_.y_ + lhs.y_.y_ * rhs.y_.y_ + lhs.y_.z_ * rhs.z_.y_ + lhs.y_.w_ * rhs.w_.y_;
        m.y_.z_ = lhs.y_.x_ * rhs.x_.z_ + lhs.y_.y_ * rhs.y_.z_ + lhs.y_.z_ * rhs.z_.z_ + lhs.y_.w_ * rhs.w_.z_;
        m.y_.w_ = lhs.y_.x_ * rhs.x_.w_ + lhs.y_.y_ * rhs.y_.w_ + lhs.y_.z_ * rhs.z_.w_ + lhs.y_.w_ * rhs.w_.w_;
        m.z_.x_ = lhs.z_.x_ * rhs.x_.x_ + lhs.z_.y_ * rhs.y_.x_ + lhs.z_.z_ * rhs.z_.x_ + lhs.z_.w_ * rhs.w_.x_;
        m.z_.y_ = lhs.z_.x_ * rhs.x_.y_ + lhs.z_.y_ * rhs.y_.y_ + lhs.z_.z_ * rhs.z_.y_ + lhs.z_.w_ * rhs.w_.y_;
        m.z_.z_ = lhs.z_.x_ * rhs.x_.z_ + lhs.z_.y_ * rhs.y_.z_ + lhs.z_.z_ * rhs.z_.z_ + lhs.z_.w_ * rhs.w_.z_;
        m.z_.w_ = lhs.z_.x_ * rhs.x_.w_ + lhs.z_.y_ * rhs.y_.w_ + lhs.z_.z_ * rhs.z_.w_ + lhs.z_.w_ * rhs.w_.w_;
        m.w_.x_ = lhs.w_.x_ * rhs.x_.x_ + lhs.w_.y_ * rhs.y_.x_ + lhs.w_.z_ * rhs.z_.x_ + lhs.w_.w_ * rhs.w_.x_;
        m.w_.y_ = lhs.w_.x_ * rhs.x_.y_ + lhs.w_.y_ * rhs.y_.y_ + lhs.w_.z_ * rhs.z_.y_ + lhs.w_.w_ * rhs.w_.y_;
        m.w_.z_ = lhs.w_.x_ * rhs.x_.z_ + lhs.w_.y_ * rhs.y_.z_ + lhs.w_.z_ * rhs.z_.z_ + lhs.w_.w_ * rhs.w_.z_;
        m.w_.w_ = lhs.w_.x_ * rhs.x_.w_ + lhs.w_.y_ * rhs.y_.w_ + lhs.w_.z_ * rhs.z_.w_ + lhs.w_.w_ * rhs.w_.w_;
        return m;

    }


    Vec4Template<T> operator * (const Vec4Template<T>& b) const
    {
        return xform(b);
    }
    
    Vec3Template<T> xform(const Vec3Template<T>& b) const {
        Vec4Template<T> a(b);
        Vec4Template<T> a2 = xform(a);
        Vec3Template<T> a3(a2.x_, a2.y_, a2.z_);
        return a3;
    }
    
    Vec4Template<T> xform(const Vec4Template<T>& b) const {
        Vec4Template<T> v;
        v.x_ = x_.x_ * b.x_ + x_.y_ * b.y_ + x_.z_ * b.z_ + x_.w_ * b.w_;
        v.y_ = y_.x_ * b.x_ + y_.y_ * b.y_ + y_.z_ * b.z_ + y_.w_ * b.w_;
        v.z_ = z_.x_ * b.x_ + z_.y_ * b.y_ + z_.z_ * b.z_ + z_.w_ * b.w_;
        v.w_ = w_.x_ * b.x_ + w_.y_ * b.y_ + w_.z_ * b.z_ + w_.w_ * b.w_;
        return v;
    }
    

    Mtx4Template& operator *= (const Mtx4Template& b)
    {
        Mtx4Template m = *this * b;
        return (*this = m);
    }
    Mtx4Template transposed() const
    {
        Mtx4Template m;
        m.x_.x_ = x_.x_; m.x_.y_ = y_.x_; m.x_.z_ = z_.x_; m.x_.w_ = w_.x_;
        m.y_.x_ = x_.y_; m.y_.y_ = y_.y_; m.y_.z_ = z_.y_; m.y_.w_ = w_.y_;
        m.z_.x_ = x_.z_; m.z_.y_ = y_.z_; m.z_.z_ = z_.z_; m.z_.w_ = w_.z_;
        m.w_.x_ = x_.w_; m.w_.y_ = y_.w_; m.w_.z_ = z_.w_; m.w_.w_ = w_.w_;
        return m;
    }
    
    Mtx3Template<T> toMat3() const
    {
        Mtx3Template<T> m;
        m.x_.x_ = x_.x_; m.y_.x_ = y_.x_; m.z_.x_ = z_.x_;
        m.x_.y_ = x_.y_; m.y_.y_ = y_.y_; m.z_.y_ = z_.y_;
        m.x_.z_ = x_.z_; m.y_.z_ = y_.z_; m.z_.z_ = z_.z_;
        return m;
    }
    
    T* pointer() {
        return &x_.x_;
    }
    
    const T* pointer() const
    {
        return &x_.x_;
    }
    
    void identity()
    {
        x_.x_ = 1; x_.y_ = 0; x_.z_ = 0; x_.w_ = 0;
        y_.x_ = 0; y_.y_ = 1; y_.z_ = 0; y_.w_ = 0;
        z_.x_ = 0; z_.y_ = 0; z_.z_ = 1; z_.w_ = 0;
        w_.x_ = 0; w_.y_ = 0; w_.z_ = 0; w_.w_ = 1;
    }
    
    static Mtx4Template<T> getIdentity()
    {
        return Mtx4Template();
    }
    
    void translate(const Vec3Template<T>& v)
    {
        makeTranslateMatrix( *this, v.x_, v.y_, v.z_ );
    }
    
    void translate( T x, T y, T z )
    {
        makeTranslateMatrix( *this, x, y, z );
    }
    
    static Mtx4Template<T> getTranslateMatrix( T x, T y, T z)
    {
        Mtx4Template m;
        makeTranslateMatrix( m, x, y, z );
        return m;
    }
    
    static void makeTranslateMatrix(
        Mtx4Template<T>& mtx,
        T x,
        T y,
        T z
    ) {
        mtx.x_.x_ = 1; mtx.x_.y_ = 0; mtx.x_.z_ = 0; mtx.x_.w_ = 0;
        mtx.y_.x_ = 0; mtx.y_.y_ = 1; mtx.y_.z_ = 0; mtx.y_.w_ = 0;
        mtx.z_.x_ = 0; mtx.z_.y_ = 0; mtx.z_.z_ = 1; mtx.z_.w_ = 0;
        mtx.w_.x_ = x; mtx.w_.y_ = y; mtx.w_.z_ = z; mtx.w_.w_ = 1;
    }
    
    void setPosition(
        T x,
        T y,
        T z
    ) {
        w_.x_ = x;
        w_.y_ = y;
        w_.z_ = z;
    }
    
    Vec3Template<T> getPosition() const {
        return Vec3Template<T>(w_.x_, w_.y_, w_.z_);
    }
    
    
    
    void scale( T s )
    {
        makeScaleMatrix( *this, s, s, s );
    }
    
    void scale( const Vec3Template<T> v )
    {
        makeScaleMatrix( *this, v.x_, v.y_, v.z_ );
    }
    
    void scale( T x, T y, T z )
    {
        makeScaleMatrix( *this, x, y, z );
    }
    
    static Mtx4Template<T> getScaleMatrix( T x, T y, T z )
    {
        Mtx4Template m;
        makeScaleMatrix( m, x, y, z );
        return m;
    }
    
    static void makeScaleMatrix( Mtx4Template<T>& m, T x, T y, T z)
    {
        m.x_.x_ = x; m.x_.y_ = 0; m.x_.z_ = 0; m.x_.w_ = 0;
        m.y_.x_ = 0; m.y_.y_ = y; m.y_.z_ = 0; m.y_.w_ = 0;
        m.z_.x_ = 0; m.z_.y_ = 0; m.z_.z_ = z; m.z_.w_ = 0;
        m.w_.x_ = 0; m.w_.y_ = 0; m.w_.z_ = 0; m.w_.w_ = 1;
    }
    
    void rotateX(T r) {
        makeRotateMatrixX(*this, r);
    }
    
    void rotateY(T r) {
        makeRotateMatrixY(*this, r);
    }
    
    void rotateZ(T r) {
        makeRotateMatrixZ(*this, r);
    }
    
    void rotate(Vec3Template<T> v) {
        makeRotateYawPitchRoll(*this, v.y_, v.x_, v.z_);
    }
    
    
    static Mtx4Template<T> getRotateMatrixZ(
        T degrees
    ) {
        Mtx4Template m;
        return makeRotateMatrixZ(m, degrees);
    }
    
    static Mtx4Template<T>& makeRotateMatrixX(
        Mtx4Template<T>& m,
        T degrees
    ) {
        T radians = t3::toRadian( degrees );
        T sin = std::sinf(radians);
        T cos = std::cosf(radians);

        m.x_.x_ = 1.0f;  m.x_.y_ = 0.0f;  m.x_.z_ = 0.0f;  m.x_.w_ = 0.0f;
        m.y_.x_ = 0.0f;  m.y_.y_ = cos;   m.y_.z_ = -sin;  m.y_.w_ = 0.0f;
		m.z_.x_ = 0.0f;  m.z_.y_ = sin;   m.z_.z_ =  cos;  m.z_.w_ = 0.0f;
		m.w_.x_ = 0.0f;  m.w_.y_ = 0.0f;  m.w_.z_ = 0.0f;  m.w_.w_ = 1.0f;
        return m;
    }
    
			 
	static Mtx4Template<T>& makeRotateMatrixY(
        Mtx4Template<T>& m,
        T degrees
    ) {
        T radians = t3::toRadian( degrees );
        T sin = std::sinf(radians);
        T cos = std::cosf(radians);
    
        m.x_.x_ =  cos;  m.x_.y_ = 0.0f;  m.x_.z_ =  sin;  m.x_.w_ = 0.0f;
        m.y_.x_ = 0.0f;  m.y_.y_ = 1.0f;  m.y_.z_ = 0.0f;  m.y_.w_ = 0.0f;
        m.z_.x_ = -sin;  m.z_.y_ = 0.0f;  m.z_.z_ =  cos;  m.z_.w_ = 0.0f;
		m.w_.x_ = 0.0f;  m.w_.y_ = 0.0f;  m.w_.z_ = 0.0f;  m.w_.w_ = 1.0f;
	
        return m;
    }
	
    static Mtx4Template<T>& makeRotateMatrixZ(
        Mtx4Template<T>& m,
        T degrees
    ) {
        T radians = t3::toRadian( degrees );
        T sin = std::sinf(radians);
        T cos = std::cosf(radians);
        
        m.x_.x_ =  cos;  m.x_.y_ =  sin;  m.x_.z_ = 0.0f;  m.x_.w_ = 0.0f;
        m.y_.x_ = -sin;  m.y_.y_ =  cos;  m.y_.z_ = 0.0f;  m.y_.w_ = 0.0f;
        m.z_.x_ = 0.0f;  m.z_.y_ = 0.0f;  m.z_.z_ = 1.0f;  m.z_.w_ = 0.0f;
        m.w_.x_ = 0.0f;  m.w_.y_ = 0.0f;  m.w_.z_ = 0.0f;  m.w_.w_ = 1.0f;
    
        return m;
    }
    
    static void makeRotateYawPitchRoll(
        Mtx4Template<T>& m,
        T yaw,
        T pitch,
        T roll
    ) {
        Mtx4Template yaw_mtx;
        makeRotateMatrixY(yaw_mtx, yaw);
        
        Mtx4Template pitch_mtx;
        makeRotateMatrixX(pitch_mtx, pitch);
        
        Mtx4Template roll_mtx;
        makeRotateMatrixZ(roll_mtx, roll);
        
        m = yaw_mtx * pitch_mtx * roll_mtx;
    }
    
    
    static void makeRotateAxis(
        Mtx4Template<T>& pOut,
        const Vec3Template<T>& pAxis,
        T fRad
    ){
    
        Vec3Template<T> vN;
        float s, c;             // sinTheta, cosTheta
        float t;                // ( 1 - cosTheta )
        float x, y, z;          // x, y, z components of normalized axis
        float xSq, ySq, zSq;    // x, y, z squared



        s = ::std::sinf(fRad);
        c = ::std::cosf(fRad);
        t = 1.0f - c;

        vN = pAxis.getNormalized();

        x = vN.x_;
        y = vN.y_;
        z = vN.z_;

        xSq = x * x;
        ySq = y * y;
        zSq = z * z;

        pOut.x_.x_ = ( t * xSq )   + ( c );
        pOut.x_.y_ = ( t * x * y ) - ( s * z );
        pOut.x_.z_ = ( t * x * z ) + ( s * y );
        pOut.x_.w_ = 0.0f;

        pOut.y_.x_ = ( t * x * y ) + ( s * z );
        pOut.y_.y_ = ( t * ySq )   + ( c );
        pOut.y_.z_ = ( t * y * z ) - ( s * x );
        pOut.y_.w_ = 0.0f;

        pOut.z_.x_ = ( t * x * z ) - ( s * y );
        pOut.z_.y_ = ( t * y * z ) + ( s * x );
        pOut.z_.z_ = ( t * zSq )   + ( c );
        pOut.z_.w_ = 0.0f;
    
        pOut.w_.x_ = 0.0f;
        pOut.w_.y_ = 0.0f;
        pOut.w_.z_ = 0.0f;
        pOut.w_.w_ = 1.0f;
    }
    
    
    void ortho( T left, T right, T bottom, T top, T near, T far ){
        makeOrthoMatrix( *this, left, right, bottom, top, near, far );
    }
    
    static void makeOrthoMatrix( Mtx4Template<T>& mtx, T left, T right, T bottom, T top, T near, T far)
    {
        T a = 2.0f / (right - left);
        T b = 2.0f / (top - bottom);
        T c = -2.0f / (far - near);
        T tx = -(right + left) / (right - left);
        T ty = -(top + bottom) / (top - bottom);
        T tz = -(far + near) / (far - near);
        
        mtx.x_.x_ = a; mtx.x_.y_ = 0; mtx.x_.z_ = 0; mtx.x_.w_ = 0;
        mtx.y_.x_ = 0; mtx.y_.y_ = b; mtx.y_.z_ = 0; mtx.y_.w_ = 0;
        mtx.z_.x_ = 0; mtx.z_.y_ = 0; mtx.z_.z_ = c; mtx.z_.w_ = 0;
        mtx.w_.x_ = tx; mtx.w_.y_ = ty; mtx.w_.z_ = tz; mtx.w_.w_ = 1;
    }
    static Mtx4Template<T> getOrthoMatrix(T left, T right, T bottom, T top, T near, T far)
    {
        Mtx4Template m;
        makeOrthoMatrix( m, left, right, bottom, top, near, far );
        return m;
    }
    
    void frustum( T left, T right, T bottom, T top, T near, T far ){
        makeFrustumMatrix( *this, left, right, bottom, top, near, far );
    }
    
    
    static void makeFrustumMatrix( Mtx4Template<T>& mtx, T left, T right, T bottom, T top, T near, T far )
    {
        T a = 2 * near / (right - left);
        T b = 2 * near / (top - bottom);
        T c = (right + left) / (right - left);
        T d = (top + bottom) / (top - bottom);
        T e = - (far + near) / (far - near);
        T f = -2 * far * near / (far - near);
      
        mtx.x_.x_ = a; mtx.x_.y_ = 0; mtx.x_.z_ = 0; mtx.x_.w_ = 0;
        mtx.y_.x_ = 0; mtx.y_.y_ = b; mtx.y_.z_ = 0; mtx.y_.w_ = 0;
        mtx.z_.x_ = c; mtx.z_.y_ = d; mtx.z_.z_ = e; mtx.z_.w_ = -1;
        mtx.w_.x_ = 0; mtx.w_.y_ = 0; mtx.w_.z_ = f; mtx.w_.w_ = 0;
    }
    
    static Mtx4Template<T> getFrustumMatrix( T left, T right, T bottom, T top, T near, T far )
    {
        Mtx4Template m;
        makeFrustumMatrix( m, left, right, bottom, top, near, far );
        return m;
    }


    void lookat(
        const Vec3Template<T>& eye,
        const Vec3Template<T>& target,
        const Vec3Template<T>& up
    ){
        makeLookAtMatrix( *this, eye, target, up );
    }
    
    static void makeLookAtMatrix(
        Mtx4Template<T>& mtx,
        const Vec3Template<T>& eye,
        const Vec3Template<T>& target,
        const Vec3Template<T>& up
    ){
        Vec3Template<T> z = (eye - target).getNormalized();
        Vec3Template<T> x = up.crossProduct(z).getNormalized();
        Vec3Template<T> y = z.crossProduct(x).getNormalized();
        
        
        mtx.x_ = Vec4Template<T>(x.x_, x.y_, x.z_, 0);
        mtx.y_ = Vec4Template<T>(y.x_, y.y_, y.z_, 0);
        mtx.z_ = Vec4Template<T>(z.x_, z.y_, z.z_, 0);
        mtx.w_ = Vec4Template<T>(0, 0, 0, 1);
        
        Vec4Template<T> eyePrime = mtx * Vec4Template<T>(
            -eye.x_,
            -eye.y_,
            -eye.z_,
            1
        );
        mtx = mtx.transposed();
        mtx.w_ = eyePrime;        
    }
    
    static Mtx4Template<T> getLookAtMatrix( 
        const Vec3Template<T>& eye,
        const Vec3Template<T>& target,
        const Vec3Template<T>& up
    ){
        Mtx4Template m;
        makeLookAtMatrix( m, eye, target, up );
        return m;
    }
    
    

    static bool makeInverseMatrix(
        Mtx4Template<T>& dest,
        const Mtx4Template<T> src
    ) {
        const T* m1 = src.pointer();
        T* m2 = dest.pointer();
    
        int i;
        int j;
        int k;
        double lu[20];
        double* plu[4];
        double det;
  
        
        for (j = 0; j < 4; ++j) {
            double max = fabs(*(plu[j] = lu + 5 * j) = *(m1++));
            for (i = 0; ++i < 4;) {
                double a = fabs(plu[j][i] = *(m1++));

                if (a > max) max = a;

            }

            if (max == 0.0) return false;

            plu[j][4] = 1.0 / max;
        }
  
        det = 1.0;
  
        
        for (j = 0; j < 4; ++j) {
            double max = fabs(plu[j][j] * plu[j][4]);
            i = j;
            for (k = j; ++k < 4;) {
                double a = fabs(plu[k][j] * plu[k][4]);
                if (a > max) {
                    max = a;
                    i = k;
                }
            }
    
            if (i > j) {
                double *t = plu[j];
                plu[j] = plu[i];
                plu[i] = t;
                det = -det;
            }
            if (plu[j][j] == 0.0) return false;
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
                m2[i * 4 + k] = (plu[i] == lu + k * 5) ? 1.0 : 0.0;
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
    
    Vec4Template<T> x_;
    Vec4Template<T> y_;
    Vec4Template<T> z_;
    Vec4Template<T> w_;
};


//  typedef
typedef Mtx2Template<float> Mtx2;
typedef Mtx3Template<float> Mtx3;
typedef Mtx4Template<float> Mtx4;
    
}   // namespace math
}   // namespace t3

#endif // TRI_MATRIX_HPP_INCLUDED

