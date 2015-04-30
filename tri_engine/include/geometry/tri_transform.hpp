


#ifndef TRI_TRANSFORM_HPP_INCLUDED
#define TRI_TRANSFORM_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "math/tri_vec3.hpp"
#include "base/tri_types.hpp"
#include "base/tri_std.hpp"

namespace t3 {


class Transform2D
    :  Uncopyable
{
public:
    Transform2D()
        : position_(0, 0)
        , rotation_(0, 0, 0)
        , scale_(1.0f, 1.0f)
        , parent_(nullptr)
    {
    }
    
    ~Transform2D() = default;

public:
    //  位置
    Vec2& position() {
        return position_;
    }
    
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
    Vec3& rotation() {
        return rotation_;
    }
    
    const Vec3& rotation() const {
        return rotation_;
    }
    
    void rotation(
        const Vec3& rot
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

    void parent(
        SharedPtr<Transform2D> p
    ) {
        parent_ = p;
    }
    
    bool hasParent() const {
        return parent_ != nullptr;
    }
    
    SharedPtr<Transform2D> parent() {
        return parent_;
    }
    
    const SharedPtr<Transform2D> parent() const {
        return parent_;
    }

    t3::Vec2 globalPosition() const {
        if (!hasParent()) {
            //  親が居ないのでただ座標を返す
            return position_;
        }
        
        //  親が居る
        //  親の情報と掛けあわせてグローバル座標を計算
        
        
        //  親の回転の影響を受けた座標
        float parent_rotate = toRadian(parent_->globalRotation().z_);
        float cos_angle = std::cos(parent_rotate);
        float sin_angle = std::sin(parent_rotate);

        t3::Vec2 rotate_pos(
            (position_.x_ * cos_angle) - (position_.y_ * sin_angle),
            (position_.x_ * sin_angle) + (position_.y_ * cos_angle)
        );

        rotate_pos += parent_->globalPosition();
        return rotate_pos;
    }
    
    
    Vec3 globalRotation() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return rotation_;
        }
        
        //  親がいる
        return rotation_ + parent_->globalRotation();
    }

    t3::Vec2 globalScale() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return scale_;
        }
        
        
        return scale_ * parent_->globalScale();
    }


private:
    Vec2 position_;
    Vec3 rotation_;
    Vec2 scale_;
    SharedPtr<Transform2D> parent_;
};

using Transform2DPtr = SharedPtr<Transform2D>;


}   // namespace t3


#endif  // TRI_TRANSFORM_HPP_INCLUDED



