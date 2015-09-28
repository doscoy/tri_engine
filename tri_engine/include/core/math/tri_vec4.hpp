////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_vec4.hpp
    ４次元ベクトル.
*/
#ifndef TRI_VEC4_HPP_INCLUDED
#define TRI_VEC4_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_vec3.hpp"

TRI_CORE_NS_BEGIN



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
    {}
    
    ///
    /// コンストラクタ
    Vec4Template(Vec3Template<T> v, T w)
        : x_(v.x_)
        , y_(v.y_)
        , z_(v.z_)
        , w_(w)
    {}
    
    
    
    ///
    /// ポインタを取得
    const T* pointer() const {
        return &x_;
    }
  
};


//  typedef
typedef Vec4Template<float>   Vec4;
typedef Vec4Template<int>     Point4;
    

TRI_CORE_NS_END



#endif // TRI_VEC4_HPP_INCLUDED
