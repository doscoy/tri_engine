/**
    @file tri_vec4.hpp
    ４次元ベクトル.
*/
#ifndef TRI_VEC4_HPP_INCLUDED
#define TRI_VEC4_HPP_INCLUDED

//  include
#include "tri_vec3.hpp"

namespace t3 {


///
/// vec4
template <typename T>
class Vec4Template {
public:
    T x_;   ///< x要素
    T y_;   ///< y要素
    T z_;   ///< z要素
    T w_;   ///< w要素
    
    ///
    /// コンストラクタ
    Vec4Template()
    {}
        
    ///
    /// コンストラクタ
    Vec4Template( T x, T y, T z, T w )
        : x_(x)
        , y_(y)
        , z_(z)
        , w_(w)
    {}
    
    ///
    /// コンストラクタ
    Vec4Template(Vec3Template<T> v)
        : x_(v.x_)
        , y_(v.y_)
        , z_(v.z_)
        , w_(1.0f)
    {
    }
    
    ///
    /// ポインタを取得
    const T* pointer() const {
        return &x_;
    }
  
};


//  typedef
typedef Vec4Template<float>   Vec4;
typedef Vec4Template<int>     Point4;
    

}   // namespace t3



#endif // TRI_VEC4_HPP_INCLUDED
