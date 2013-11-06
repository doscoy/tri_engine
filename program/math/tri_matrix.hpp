

#ifndef TRI_MATRIX_HPP_INCLUDED
#define TRI_MATRIX_HPP_INCLUDED

//  include
#include "tri_vec2.hpp"
#include "tri_vec3.hpp"
#include "tri_vec4.hpp"
#include "../math/tri_math_util.hpp"


namespace t3 {

// Mtx2Template
template <typename T>
struct Mtx2Template {
    Mtx2Template()
    {
        x.x = 1; x.y = 0;
        y.x = 0; y.y = 1;
    }
    Mtx2Template(const T* m)
    {
        x.x = m[0]; x.y = m[1];
        y.x = m[2]; y.y = m[3];
    }
    Vec2Template<T> x;
    Vec2Template<T> y;
};


template <typename T>
struct Mtx3Template {
    Mtx3Template()
    {
        x.x = 1; x.y = 0; x.z = 0;
        y.x = 0; y.y = 1; y.z = 0;
        z.x = 0; z.y = 0; z.z = 1;
    }
    Mtx3Template(const T* m)
    {
        x.x = m[0]; x.y = m[1]; x.z = m[2];
        y.x = m[3]; y.y = m[4]; y.z = m[5];
        z.x = m[6]; z.y = m[7]; z.z = m[8];
    }
    Mtx3Template(Vec3 x, Vec3 y, Vec3 z) : x(x), y(y), z(z)
    {
    }
    Mtx3Template transposed() const
    {
        Mtx3Template m;
        m.x.x = x.x; m.x.y = y.x; m.x.z = z.x;
        m.y.x = x.y; m.y.y = y.y; m.y.z = z.y;
        m.z.x = x.z; m.z.y = y.z; m.z.z = z.z;
        return m;
    }
    const T* Pointer() const
    {
        return &x.x;
    }
    Vec3Template<T> x;
    Vec3Template<T> y;
    Vec3Template<T> z;
};

template <typename T>
struct Mtx4Template {
    Mtx4Template()
    {
        identity();
    }
    Mtx4Template(const Mtx3Template<T>& m)
    {
        x.x = m.x.x; x.y = m.x.y; x.z = m.x.z; x.w = 0;
        y.x = m.y.x; y.y = m.y.y; y.z = m.y.z; y.w = 0;
        z.x = m.z.x; z.y = m.z.y; z.z = m.z.z; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    Mtx4Template(const T* m)
    {
        x.x = m[0];  x.y = m[1];  x.z = m[2];  x.w = m[3];
        y.x = m[4];  y.y = m[5];  y.z = m[6];  y.w = m[7];
        z.x = m[8];  z.y = m[9];  z.z = m[10]; z.w = m[11];
        w.x = m[12]; w.y = m[13]; w.z = m[14]; w.w = m[15];
    }
    Mtx4Template operator * (const Mtx4Template& b) const
    {
        Mtx4Template m;
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

    Vec4Template<T> operator * (const Vec4Template<T>& b) const
    {
        return xform(b);
    }
    
    Vec4Template<T> xform(const Vec4Template<T>& b) const {
        Vec4Template<T> v;
        v.x = x.x * b.x + x.y * b.y + x.z * b.z + x.w * b.w;
        v.y = y.x * b.x + y.y * b.y + y.z * b.z + y.w * b.w;
        v.z = z.x * b.x + z.y * b.y + z.z * b.z + z.w * b.w;
        v.w = w.x * b.x + w.y * b.y + w.z * b.z + w.w * b.w;
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
        m.x.x = x.x; m.x.y = y.x; m.x.z = z.x; m.x.w = w.x;
        m.y.x = x.y; m.y.y = y.y; m.y.z = z.y; m.y.w = w.y;
        m.z.x = x.z; m.z.y = y.z; m.z.z = z.z; m.z.w = w.z;
        m.w.x = x.w; m.w.y = y.w; m.w.z = z.w; m.w.w = w.w;
        return m;
    }
    
    Mtx3Template<T> toMat3() const
    {
        Mtx3Template<T> m;
        m.x.x = x.x; m.y.x = y.x; m.z.x = z.x;
        m.x.y = x.y; m.y.y = y.y; m.z.y = z.y;
        m.x.z = x.z; m.y.z = y.z; m.z.z = z.z;
        return m;
    }
    
    T* pointer() {
        return &x.x;
    }
    
    const T* pointer() const
    {
        return &x.x;
    }
    
    void identity()
    {
        x.x = 1; x.y = 0; x.z = 0; x.w = 0;
        y.x = 0; y.y = 1; y.z = 0; y.w = 0;
        z.x = 0; z.y = 0; z.z = 1; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    
    static Mtx4Template<T> getIdentity()
    {
        return Mtx4Template();
    }
    
    void translate(const Vec3Template<T>& v)
    {
        makeTranslateMatrix( *this, v.x, v.y, v.z );
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
        mtx.x.x = 1; mtx.x.y = 0; mtx.x.z = 0; mtx.x.w = 0;
        mtx.y.x = 0; mtx.y.y = 1; mtx.y.z = 0; mtx.y.w = 0;
        mtx.z.x = 0; mtx.z.y = 0; mtx.z.z = 1; mtx.z.w = 0;
        mtx.w.x = x; mtx.w.y = y; mtx.w.z = z; mtx.w.w = 1;
    }
    
    void setPosition(
        T x,
        T y,
        T z
    ) {
        w.x = x;
        w.y = y;
        w.z = z;
    }
    
    Vec3Template<T> getPosition() const {
        return Vec3Template<T>(w.x, w.y, w.z);
    }
    
    
    
    void scale( T s )
    {
        makeScaleMatrix( *this, s, s, s );
    }
    
    void scale( const Vec3Template<T> v )
    {
        makeScaleMatrix( *this, v.x, v.y, v.z );
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
        m.x.x = x; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = y; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = z; m.z.w = 0;
        m.w.x = 0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
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
        makeRotateYawPitchRoll(*this, v.y, v.x, v.z);
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

        m.x.x = 1.0f;  m.x.y = 0.0f;  m.x.z = 0.0f;  m.x.w = 0.0f;
        m.y.x = 0.0f;  m.y.y = cos;   m.y.z = -sin;  m.y.w = 0.0f;
		m.z.x = 0.0f;  m.z.y = sin;   m.z.z =  cos;  m.z.w = 0.0f;
		m.w.x = 0.0f;  m.w.y = 0.0f;  m.w.z = 0.0f;  m.w.w = 1.0f;
        return m;
    }
    
			 
	static Mtx4Template<T>& makeRotateMatrixY(
        Mtx4Template<T>& m,
        T degrees
    ) {
        T radians = t3::toRadian( degrees );
        T sin = std::sinf(radians);
        T cos = std::cosf(radians);
    
        m.x.x =  cos;  m.x.y = 0.0f;  m.x.z =  sin;  m.x.w = 0.0f;
        m.y.x = 0.0f;  m.y.y = 1.0f;  m.y.z = 0.0f;  m.y.w = 0.0f;
        m.z.x = -sin;  m.z.y = 0.0f;  m.z.z =  cos;  m.z.w = 0.0f;
		m.w.x = 0.0f;  m.w.y = 0.0f;  m.w.z = 0.0f;  m.w.w = 1.0f;
	
        return m;
    }
	
    static Mtx4Template<T>& makeRotateMatrixZ(
        Mtx4Template<T>& m,
        T degrees
    ) {
        T radians = t3::toRadian( degrees );
        T sin = std::sinf(radians);
        T cos = std::cosf(radians);
        
        m.x.x =  cos;  m.x.y =  sin;  m.x.z = 0.0f;  m.x.w = 0.0f;
        m.y.x = -sin;  m.y.y =  cos;  m.y.z = 0.0f;  m.y.w = 0.0f;
        m.z.x = 0.0f;  m.z.y = 0.0f;  m.z.z = 1.0f;  m.z.w = 0.0f;
        m.w.x = 0.0f;  m.w.y = 0.0f;  m.w.z = 0.0f;  m.w.w = 1.0f;
    
        return m;
    }
    
    static Mtx4Template<T>& makeRotateYawPitchRoll(
        Mtx4Template<T>& m,
        T yaw,
        T pitch,
        T roll
    ) {
        Mtx4Template yaw_mtx;
        makeRotateMatrixY(yaw_mtx, yaw);
        
        Mtx4Template pitch_mtx;
        makeRotateMatrixY(pitch_mtx, pitch);
        
        Mtx4Template roll_mtx;
        makeRotateMatrixY(roll_mtx, roll);
        
        m = yaw_mtx * pitch_mtx * roll_mtx;

        return m;
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
        
        mtx.x.x = a; mtx.x.y = 0; mtx.x.z = 0; mtx.x.w = 0;
        mtx.y.x = 0; mtx.y.y = b; mtx.y.z = 0; mtx.y.w = 0;
        mtx.z.x = 0; mtx.z.y = 0; mtx.z.z = c; mtx.z.w = 0;
        mtx.w.x = tx; mtx.w.y = ty; mtx.w.z = tz; mtx.w.w = 1;
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
      
        mtx.x.x = a; mtx.x.y = 0; mtx.x.z = 0; mtx.x.w = 0;
        mtx.y.x = 0; mtx.y.y = b; mtx.y.z = 0; mtx.y.w = 0;
        mtx.z.x = c; mtx.z.y = d; mtx.z.z = e; mtx.z.w = -1;
        mtx.w.x = 0; mtx.w.y = 0; mtx.w.z = f; mtx.w.w = 0;
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
        
        
        mtx.x = Vec4Template<T>(x.x, x.y, x.z, 0);
        mtx.y = Vec4Template<T>(y.x, y.y, y.z, 0);
        mtx.z = Vec4Template<T>(z.x, z.y, z.z, 0);
        mtx.w = Vec4Template<T>(0, 0, 0, 1);
        
        Vec4Template<T> eyePrime = mtx * Vec4Template<T>(-eye.x, -eye.y, -eye.z, 1);
        mtx = mtx.transposed();
        mtx.w = eyePrime;        
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
    
    Vec4Template<T> x;
    Vec4Template<T> y;
    Vec4Template<T> z;
    Vec4Template<T> w;
};


//  typedef
typedef Mtx2Template<float> Mtx2;
typedef Mtx3Template<float> Mtx3;
typedef Mtx4Template<float> Mtx4;
    

}   // namespace t3

#endif // TRI_MATRIX_HPP_INCLUDED

