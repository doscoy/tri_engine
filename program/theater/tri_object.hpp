

#ifndef TRI_OBJECT_HPP_INCLUDED
#define TRI_OBJECT_HPP_INCLUDED

#include "../math/tri_math.hpp"

namespace t3 {
inline namespace theater {


class Object
{
public:
    Object() = default;
    virtual ~Object() = default;


public:
    void setPosition(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        position_.x = x;
        position_.y = y;
        position_.z = z;
    }
    
    void setPosition(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ = v;
    }
    
    const Vec3& getPosition() const {
        return position_;
    }
    
    
    void setRotation(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        rotation_.x = x;
        rotation_.y = y;
        rotation_.z = z;
    }
    
    void setRotation(
        const Vec3& v
    ) {
        calc_request_ = true;
        rotation_ = v;
    }
    
    const Vec3& getRotation() const {
        return rotation_;
    }
    
    
    
    void setScale(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        scale_.x = x;
        scale_.y = y;
        scale_.z = z;
    }
    
    void setScale(
        const Vec3& v
    ) {
        calc_request_ = true;
        scale_ = v;
    }
    
    const Vec3& getScale() const {
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

    const Mtx4* getTransformMatrix();

private:
    void makeTransformMatrix();


private:
    Vec3 position_;
    Vec3 rotation_;
    Vec3 scale_;
    bool visible_;
    Mtx4 transform_;
    bool calc_request_;
};



}   // namespace theater
}   // namespace t3



#endif  // TRI_OBJECT_HPP_INCLUDED
