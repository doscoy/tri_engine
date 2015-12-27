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
class Vec4 {
    using element_t = float;
public:
    element_t x_;   ///< x要素
    element_t y_;   ///< y要素
    element_t z_;   ///< z要素
    element_t w_;   ///< w要素
    
    ///
    /// コンストラクタ
    Vec4()
    {}
        
    ///
    /// コンストラクタ
    Vec4( element_t x, element_t y, element_t z, element_t w )
        : x_(x)
        , y_(y)
        , z_(z)
        , w_(w)
    {}
    
    ///
    /// コンストラクタ
    Vec4(Vec3 v)
        : x_(v.x_)
        , y_(v.y_)
        , z_(v.z_)
        , w_(1.0f)
    {}
    
    ///
    /// コンストラクタ
    Vec4(Vec3 v, element_t w)
        : x_(v.x_)
        , y_(v.y_)
        , z_(v.z_)
        , w_(w)
    {}
    
    
    
    ///
    /// ポインタを取得
    const element_t* pointer() const {
        return &x_;
    }
  
};

    

TRI_CORE_NS_END



#endif // TRI_VEC4_HPP_INCLUDED
