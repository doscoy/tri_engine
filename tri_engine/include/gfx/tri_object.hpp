

#ifndef tri_sandbox_osx_tri_object_hpp
#define tri_sandbox_osx_tri_object_hpp

#include "math/tri_math.hpp"


namespace t3 {
inline namespace theater {
    
class Object {
public:
    Object();
    ~Object();

public:
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


#endif
