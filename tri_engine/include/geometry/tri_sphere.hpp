#ifndef TRI_SPHERE_HPP_INCLUDED
#define TRI_SPHERE_HPP_INCLUDED

#include "../math/tri_vec3.hpp"

namespace t3 {
inline namespace geometry {

class Sphere
{
public:
    Sphere() = default;
    Sphere(
        const Vec3& position,
        const float radius
    )   : position_(position)
        , radius_(radius)
    
    {
    }
    
    ~Sphere() = default;
    
public:
    void radius(
        const float radius
    ) {
        radius_ = radius;
    }

    float radius() const {
        return radius_;
    }
    
    float getRadiusSq() const {
        return radius_ * radius_;
    }
    

    
    void position(
        const Vec3& position
    ) {
        position_ = position;
    }
    
    const Vec3& position() const {
        return position_;
    }
    
private:

    Vec3 position_;
    float radius_;

};

}   // geometry
}   // t3

#endif  // TRI_SPHERE_HPP_INCLUDED
