
#ifndef TRI_AABB_HPP_INCLUDED
#define TRI_AABB_HPP_INCLUDED


#include "../math/tri_vec3.hpp"

namespace t3 {
inline namespace geometry {

class AABB
{
public:
    AABB()
        : min_(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max())
        , max_(
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min())
    {}
    
    AABB(
        const Vec3& min,
        const Vec3& max
    )   : min_(min)
        , max_(max)
    {}
    
    
    
    ~AABB()
    {}
    
public:
    void addPoint(
        const Vec3& p
    ) {
        if (min_.x_ > p.x_) {
            min_.x_ = p.x_;
        }
        else if (max_.x_ < p.x_) {
            max_.x_ = p.x_;
        }
        
        if (min_.y_ > p.y_) {
            min_.y_ = p.y_;
        }
        else if (max_.y_ < p.y_) {
            max_.y_ = p.y_;
        }
        
        if (min_.z_ > p.z_) {
            min_.z_ = p.z_;
        }
        else if (max_.z_ < p.z_) {
            max_.z_ = p.z_;
        }
    }
    
    void min(const Vec3& min) {
        min_ = min;
    }

    const Vec3* min() const {
        return &min_;
    }
    
    void max(const Vec3& max) {
        max_ = max;
    }
    
    const Vec3* max() const {
        return &max_;
    }
    
    bool isInside(
        const Vec3& p
    ) const {
        if (p.x_ > max_.x_) {
            return false;
        }
        if (p.x_ < min_.x_) {
            return false;
        }
        
        if (p.y_ > max_.y_) {
            return false;
        }
        if (p.y_ < min_.y_) {
            return false;
        }
        
        if (p.z_ > max_.z_) {
            return false;
        }
        if (p.z_ < min_.z_) {
            return false;
        }
        
        return true;
    }

    void center(
        Vec3* out
    ) {
        *out = (min_ + max_) * 0.5f;
    }
    
    void getRadius(
        Vec3* out
    ) {
        *out = (max_ - min_) * 0.5f;
    }


private:
    Vec3 min_;
    Vec3 max_;

};

}   // namespace geometry
}   // namespace t3

#endif  // TRI_AABB_HPP_INCLUDED
