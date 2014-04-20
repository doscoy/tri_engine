


#ifndef TRI_TRANSFORM_HPP_INCLUDED
#define TRI_TRANSFORM_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "math/tri_vec3.hpp"
#include "base/tri_types.hpp"

namespace t3 {
inline namespace geopetry {


class Transform2D
    :  Uncopyable
{
public:
    Transform2D() = default;
    ~Transform2D() = default;

public:
    //  位置
    const Vec2& getPosition() const {
        return position_;
    }
    
    void setPosition(
        const Vec2& pos
    ) {
        position_ = pos;
    }
    
    void setPosition(
        const float x,
        const float y
    ) {
        position_.x_ = x;
        position_.y_ = y;
    }
    
    //  回転角
    const float getRotation() const {
        return rotation_;
    }
    
    
    //  スケール
    const Vec2& getScale() const {
        return scale_;
    }
    
    void setScale(
        const Vec2& scale
    ) {
        scale_ = scale;
    }
    
    void setScale(
       const float x,
       const float y
    ) {
        scale_.x_ = x;
        scale_.y_ = y;
    }

private:
    Vec2 position_;
    float rotation_;
    Vec2 scale_;
};


class Transform2DController {
public:
    Transform2DController() = default;
    ~Transform2DController() = default;
    
    virtual void initializeController(Transform2D*) {}
    virtual void controll(tick_t delta_time, Transform2D* transform) = 0;
};


}   // namespace geometry
}   // namespace t3


#endif  // TRI_TRANSFORM_HPP_INCLUDED



