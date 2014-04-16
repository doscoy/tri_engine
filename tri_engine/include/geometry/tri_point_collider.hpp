#ifndef TRI_POINT_COLLIDER_HPP_INCLUDED
#define TRI_POINT_COLLIDER_HPP_INCLUDED


#include "tri_collider.hpp"
#include "math/tri_vec2.hpp"


namespace t3 {
inline namespace geometry {
        

class CircleCollider;


class PointCollider
    : public Collider {
public:
    ~PointCollider() = default;
            
public:
    bool isHit(const CircleCollider& col) const override;
    bool isHit(const PointCollider& col) const override;
    const HashString& getType() const override;
    static const HashString TYPE;

public:
    const Vec2& getPosition() const {
        return position_;
    }

private:
    Vec2 position_;
};
        
        
}   // namaespace geometry
}   // namespace t3

#endif  // TRI_POINT_COLLIDER_HPP_INCLUDED

