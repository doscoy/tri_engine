
#ifndef TRI_PLANE_HPP_INCLUDED
#define TRI_PLANE_HPP_INCLUDED


#include "../math/tri_math.hpp"

namespace t3 {
inline namespace geometry {



class Plane
{
public:

    Plane() = default;

    Plane(
        const Vec3& a,
        const Vec3& b,
        const Vec3& c
    ) {
        Vec3 ab = b - a;
        Vec3 ac = c - a;
        normal_ = ac.crossProduct(ab);
        normal_.normalize();
        point_ = a;
        dot_np_ = point_.dotProduct(normal_);
    }
    Plane(
        const Vec3& point,
        const Vec3& normal
    )   : point_(point)
        , normal_(normal)
        , dot_np_(Vec3::getDotProduct(point, normal))
    {
    }
    
    ~Plane() = default;

public:
    bool isInside(
        const Vec3& pos
    ) const {
        Vec3 v = point_ - pos;
        float d = v.dotProduct(normal_);
        return d > 0;
    }
    
    bool isInside(
        const Vec3& pos,
        const float radius
    ) {
        Vec3 d = normal_ * radius;
		Vec3 p = pos - d;
		return isInside(p);
    }
    
    const Vec3& getPoint() const {
        return point_;
    }
    
    const Vec3& getNormal() const {
        return normal_;
    }
    
    


public:
    Vec3 point_;
    Vec3 normal_;
    float dot_np_;
};


}   // namespace geometry
}   // namespace t3

#endif  // TRI_PLANE_HPP_INCLUDED
