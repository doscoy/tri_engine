
#ifndef TRI_AABB_HPP_INCLUDED
#define TRI_AABB_HPP_INCLUDED


#include "../math/tri_vec3.hpp"

namespace t3 {
inline namespace geometry {

class Segment
{
public:
    Segment()
        : a_(0, 0, 1)
        , b_(0, 0, 0)
    {
    }
    
    Segment(
        const Vec3& a,
        const Vec3& b
    )   : a_(a)
        , b_(b)
    {}
    

    ~Segment() = default;
    
    const Vec3* getPointA() const {
        return &a_;
    }
    
    const Vec3* getPointB() const {
        return &b_;
    }

private:
    Vec3 a_;
    Vec3 b_;
};




}   // namespace geometry
}   // namespace t3


#endif // TRI_AABB_HPP_INCLUDED

