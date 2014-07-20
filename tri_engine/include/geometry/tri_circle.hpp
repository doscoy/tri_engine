
#ifndef TRI_CIRCLE_HPP_INCLUDED
#define TRI_CIRCLE_HPP_INCLUDED

#include "math/tri_vec2.hpp"

namespace t3 {
inline namespace geometry {

class Circle {
public:
    Circle()
        : Circle(Vec2(0.0f, 0.0f), 1.0f)
    {}

    Circle(
        const Vec2& pos,
        float radius
    )   : position_(pos)
        , radius_(radius)
    {}


public:
    void position(
        const Vec2& pos
    ) {
        position_ = pos;
    }

    const Vec2& position() const {
        return position_;
    }
    
    
    void radius(
        const float radius
    ) {
        radius_ = radius;
    }
    
    
    float getRadius() const {
        return radius_;
    }


private:
    Vec2 position_;
    float radius_;
};


}   // namespace geometry
}   // namespace t3


#endif  // TRI_CIRCLE_HPP_INCLUDED
