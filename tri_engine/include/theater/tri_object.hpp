

#ifndef TRI_OBJECT_HPP_INCLUDED
#define TRI_OBJECT_HPP_INCLUDED

#include "../math/tri_math.hpp"

namespace t3 {
inline namespace theater {


class Object
{
public:
    Object();
    virtual ~Object();


public:
    void position(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        position_.x_ = x;
        position_.y_ = y;
        position_.z_ = z;
    }
    
    void position(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ = v;
    }
    
    const Vec3& position() const {
        return position_;
    }
    
    void addPosition(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ += v;
    }
    
    void addPositionX(
        const float v
    ) {
        calc_request_ = true;
        position_.x_ += v;
    }
    
    void addPositionY(
        const float v
    ) {
        calc_request_ = true;
        position_.y_ += v;
    }
    void addPositionZ(
        const float v
    ) {
        calc_request_ = true;
        position_.z_ += v;
    }
    
    void rotation(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        rotation_.x_ = x;
        rotation_.y_ = y;
        rotation_.z_ = z;
    }
    
    
    void setRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ = r;
    }
    
    void setRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ = r;
    }
    
    void setRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ = r;
    }
    
    void rotation(
        const Vec3& v
    ) {
        calc_request_ = true;
        rotation_ = v;
    }
    
    const Vec3& rotation() const {
        return rotation_;
    }
    
    void addRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ += r;
    }
    
    void addRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ += r;
    }
    
    void addRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ += r;
    }
    
    void scale(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        scale_.x_ = x;
        scale_.y_ = y;
        scale_.z_ = z;
    }
    
    void scale(
        const Vec3& v
    ) {
        calc_request_ = true;
        scale_ = v;
    }
    
    const Vec3& scale() const {
        return scale_;
    }
    
    void setVisible(
        const bool visible
    ) {
        visible_ = visible;
    }

    bool isVisible() const {
        return visible_;
    }

    const Mtx44* getTransformMatrix();

private:
    void makeTransformMatrix();


private:
    Vec3 position_;
    Vec3 rotation_;
    Vec3 scale_;
    bool visible_;
    Mtx44 transform_;
    bool calc_request_;
};



}   // namespace theater
}   // namespace t3



#endif  // TRI_OBJECT_HPP_INCLUDED
