


#ifndef TRI_TRANSFORM_HPP_INCLUDED
#define TRI_TRANSFORM_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "math/tri_vec3.hpp"
#include "base/tri_types.hpp"
#include <memory>

namespace t3 {
inline namespace geopetry {


class Transform2D
    :  Uncopyable
{
public:
    Transform2D()
        : position_(0, 0)
        , rotation_(0)
        , scale_(1.0f, 1.0f)
        , parent_(nullptr)
    {
    }
    
    ~Transform2D() = default;

public:
    //  位置
    const Vec2& position() const {
        return position_;
    }
    
    void position(
        const Vec2& pos
    ) {
        position_ = pos;
    }
    
    void position(
        const float x,
        const float y
    ) {
        position_.x_ = x;
        position_.y_ = y;
    }
    
    //  回転角
    float rotation() const {
        return rotation_;
    }
    
    void rotation(
        const float rot
    ) {
        rotation_ = rot;
    }
    
    //  スケール
    Vec2& scale() {
        return scale_;
    }
    
    const Vec2& scale() const {
        return scale_;
    }
    
    void scale(
        const Vec2& scale
    ) {
        scale_ = scale;
    }
    
    void scale(
       const float x,
       const float y
    ) {
        scale_.x_ = x;
        scale_.y_ = y;
    }

    void scale(
        const float s
    ) {
        scale_.x_ = s;
        scale_.y_ = s;
    }

    void setParentTransform(
        std::shared_ptr<Transform2D> p
    ) {
        parent_ = p;
    }
    
    bool hasParent() const {
        return parent_ != nullptr;
    }

    t3::Vec2 globalPosition() const {
        if (!hasParent()) {
            //  親が居ないのでただ座標を返す
            return position_;
        }
        
        //  親が居る
        //  親の情報と掛けあわせてグローバル座標を計算
        
        //  親の回転の影響を受けた座標
        float parent_rotate = toRadian(parent_->globalRotation());
        float cos_angle = std::cos(parent_rotate);
        float sin_angle = std::sin(parent_rotate);

        t3::Vec2 rotate_pos(
            (position_.x_ * cos_angle) - (position_.y_ * sin_angle),
            (position_.x_ * sin_angle) + (position_.y_ * cos_angle)
        );

        rotate_pos += parent_->globalPosition();
        return rotate_pos;
    }
    
    
    float globalRotation() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return rotation_;
        }
        
        //  親がいる
        return rotation_ + parent_->globalRotation();
    }


private:
    Vec2 position_;
    float rotation_;
    Vec2 scale_;
    std::shared_ptr<Transform2D> parent_;
};

using Transform2DPtr = std::shared_ptr<Transform2D>;



}   // namespace geometry
}   // namespace t3


#endif  // TRI_TRANSFORM_HPP_INCLUDED



