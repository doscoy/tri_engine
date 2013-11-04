//
//  tri_sphere.hpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/11/03.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_sandbox_osx_tri_sphere_hpp
#define tri_sandbox_osx_tri_sphere_hpp

namespace t3 {
inline namespace geometry {

class Sphere
{
    Sphere() = default;
    Sphere(
        const Vec3& position,
        const flaot radius
    )   : position_(position)
        , radius_(radius)
    
    {
    }
    
    ~Sphere() = default;
    
public:
    void setRadius(
        const float radius
    ) {
        radius_ = radius;
    }
    
    void setPosition(
        const Vec3& position
    ) {
        position_ = position;
    }
    
    const Vec3& getPosition() const {
        return position_;
    }
    
    float getRadius() const {
        return radius_;
    }
    
private:

    Vec3& position_;
    float radius_;

};

}   // geometry
}   // t3

#endif
