
#ifndef TRI_RECTANGLE_HPP_INCLUDED
#define TRI_RECTANGLE_HPP_INCLUDED


#include "../math/tri_vec2.hpp"

namespace t3 {
inline namespace geometry {

class Rectangle
{
public:
    Rectangle()
        : min_(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max())
        , max_(
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min())
    {
        calcCenterFromMinMax();
    }
    
    Rectangle(
        const Vec2& min,
        const Vec2& max
    )   : min_(min)
        , max_(max)
    {
        calcCenterFromMinMax();
    }
    
    
    
    ~Rectangle()
    {
    }
    
public:

    void setupFromCenterSize(
        const Vec2& center,
        const Vec2& size
    ) {
        //  下限上限を計算
        Vec2 half_size = size / 2;
        min_ = center - half_size;
        max_ = center + half_size;
        
        //  中心
        center_ = center;
        
        //  サイズ
        size_ = size;
    }
    
    

public:
    void setMin(const Vec2& min) {
        min_ = min;
        calcCenterFromMinMax();
    }

    const Vec2& getMin() const {
        return min_;
    }
    
    void setMax(const Vec2& max) {
        max_ = max;
        calcCenterFromMinMax();
    }
    
    const Vec2& getMax() const {
        return max_;
    }

    const Vec2& getCenter() const {
        return center_;
    }
    
    const Vec2& size() const {
        return size_;
    }

    
private:
    void calcCenterFromMinMax() {
        size_ = max_ - min_;
        center_ = min_ + (size_ / 2);
    }
    
private:

    Vec2 min_;
    Vec2 max_;

    Vec2 size_;
    Vec2 center_;

};

}   // namespace geometry
}   // namespace t3

#endif  // TRI_RECTANGLE_HPP_INCLUDED
