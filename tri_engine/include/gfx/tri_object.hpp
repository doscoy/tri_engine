

#ifndef TRI_OBJECT_HPP_INCLUDED
#define TRI_OBJECT_HPP_INCLUDED


#include "math/tri_math.hpp"


namespace t3 {

    
class Object {
public:
    Object();
    ~Object();

public:
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


}   // namespace t3


#endif
