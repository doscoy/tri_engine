#ifndef TRI_CIRCLE_COLLIDER_HPP_INCLUDED
#define TRI_CIRCLE_COLLIDER_HPP_INCLUDED


#include "tri_collider.hpp"
#include "tri_circle.hpp"


namespace t3 {
inline namespace geometry {


class CircleCollider
    : public Collider {

public:
    CircleCollider(
        const HashString& name
    );
    ~CircleCollider() = default;
    
public:
    bool isHit(const CircleCollider& col) const override;
    bool isHit(const PointCollider& col) const override;
    const HashString& getCollisionType() const override;
    
public:
    static const HashString TYPE;

public:
    void setPosition(
        const Vec2& pos
    ) {
        circle_.setPosition(pos);
    }
    
    void setRadius(
        const float radius
    ) {
        circle_.setRadius(radius);
    }

    const Circle& getCircle() const {
        return circle_;
    }

private:
    Circle circle_;

};


}   // namaespace geometry
}   // namespace t3

#endif  // TRI_CIRCLE_COLLIDER_HPP_INCLUDED

