#ifndef TRI_BOX_HPP_INCLUDED
#define TRI_BOX_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"

#include "tri_object.hpp"

namespace t3 {
inline namespace theater {
    
class Box
    : public Object
{
public:
    Box()
        : size_(1,1,1)
    {}
    
    virtual ~Box()
    {}

public:
    void size(
        const Vec3& v
    ) {
        size_ = v;
    }

    void size(
        const float x,
        const float y,
        const float z
    ) {
        size_.x_ = x;
        size_.y_ = y;
        size_.z_ = z;
    }

    const Vec3& size() const {
        return size_;
    }


    void render();

private:
    Vec3 size_;
};


}   // namespace theater
}   // namespace t3

#endif  // TRI_BOX_HPP_INCLUDED
