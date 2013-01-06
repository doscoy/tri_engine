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


#include "tri_basetypes.hpp"
#include <iostream>


namespace t3 {
    
template <typename T>
struct Vec4 {
    T x;
    T y;
    T z;
    T w;
        
    Vec4()
    {}
        
    Vec4( T x, T y, T z, T w )
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}
    
    
    const T* pointer() const {
        return &x;
    }
  
    //  dump
    void dump() const {
        std::cout << "x:" << x << " y:" << y << " z:" << z << " w:" << w << std::endl;
    }
/*
    friend std::ostream& operator<<( std::ostream& os, const Vec4& v ){
        os << v.x << v.y << v.z;
        return os;
    }
*/

};


//  typedef
typedef Vec4<float>   vec4_t;
typedef Vec4<int>     ivec4_t;
    
    
}   // namespace t3



#endif // TRI_VEC4_HPP_INCLUDED
