#ifndef TRI_BOX_HPP_INCLUDED
#define TRI_BOX_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include "../platform/platform_sdk.hpp"
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
    void setSize(
        const Vec3& v
    ) {
        size_ = v;
    }

    void setSize(
        const float x,
        const float y,
        const float z
    ) {
        size_.x = x;
        size_.y = y;
        size_.z = z;
    }

    const Vec3& getSize() const {
        return size_;
    }


    void render();

private:
    Vec3 size_;
};


}   // namespace theater
}   // namespace t3

#endif  // TRI_BOX_HPP_INCLUDED
