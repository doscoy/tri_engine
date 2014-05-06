


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
    const Vec2& getLocalPosition() const {
        return position_;
    }
    
    void setLocalPosition(
        const Vec2& pos
    ) {
        position_ = pos;
    }
    
    void setLocalPosition(
        const float x,
        const float y
    ) {
        position_.x_ = x;
        position_.y_ = y;
    }
    
    //  回転角
    float getLocalRotation() const {
        return rotation_;
    }
    
    void setLocalRotation(
        const float rot
    ) {
        rotation_ = rot;
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

    void setParentTransform(
        const Transform2D* parent
    ) {
        parent_ = parent;
    }
    
    bool hasParent() const {
        return parent_ != nullptr;
    }

    t3::Vec2 getGlobalPosition() const {
        if (!hasParent()) {
            //  親が居ないのでただ座標を返す
            return position_;
        }
        
        //  親が居る
        //  親の情報と掛けあわせてグローバル座標を計算
        
        //  親の回転の影響を受けた座標
        float parent_rotate = parent_->getGlobalRotation();
        float cos_angle = std::cos(parent_rotate);
        float sin_angle = std::sin(parent_rotate);

        t3::Vec2 rotate_pos(
            (position_.x_ * cos_angle) - (position_.x_ * sin_angle),
            (position_.y_ * sin_angle) + (position_.y_ * cos_angle)
        );

        rotate_pos += parent_->getGlobalPosition();
        return rotate_pos;
    }
    
    
    float getGlobalRotation() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return rotation_;
        }
        
        //  親がいる
        return rotation_ + parent_->getGlobalRotation();
    }


private:
    Vec2 position_;
    float rotation_;
    Vec2 scale_;
    const Transform2D* parent_;
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



