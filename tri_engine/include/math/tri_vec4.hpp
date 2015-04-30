/*
 *  tri_vec4.hpp
 *  TriEngine
 *
 *  Created by 可児 哲郎 on 11/09/22.
 *  Copyright 2011  . All rights reserved.
 *
 */

#ifndef TRI_VEC4_HPP_INCLUDED
#define TRI_VEC4_HPP_INCLUDED

#include "tri_vec3.hpp"

namespace t3 {



template <typename T>
class Vec4Template {
public:
    T x_;
    T y_;
    T z_;
    T w_;
        
    Vec4Template()
    {}
        
    Vec4Template( T x, T y, T z, T w )
        : x_(x)
        , y_(y)
        , z_(z)
        , w_(w)
    {}
    
    Vec4Template(Vec3Template<T> v)
        : x_(v.x_)
        , y_(v.y_)
        , z_(v.z_)
        , w_(1.0f)
    {
    }
    
    
    const T* pointer() const {
        return &x_;
    }
  
};


//  typedef
typedef Vec4Template<float>   Vec4;
typedef Vec4Template<int>     Point4;
    

}   // namespace t3



#endif // TRI_VEC4_HPP_INCLUDED
