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
    PointCollider(const HashString& name);
    ~PointCollider(){}
            
public:
    bool isHit(const CircleCollider& col) const override;
    bool isHit(const PointCollider& col) const override;
    const HashString& getCollisionType() const override;
    static const HashString TYPE;

public:
    const Vec2& getPosition() const {
        return position_;
    }
    
    void setPosition(const Vec2& pos) {
        position_ = pos;
    }

private:
    Vec2 position_;
};
        
        
}   // namaespace geometry
}   // namespace t3

#endif  // TRI_POINT_COLLIDER_HPP_INCLUDED

