//
//  tri_object.cpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/11/04.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#include "tri_object.hpp"



namespace t3 {
inline namespace theater {



Object::Object()
    : position_(0, 0, 0)
    , rotation_(0, 0, 0)
    , scale_(1.0f, 1.0f, 1.0f)
    , visible_(true)
    , transform_()
    , calc_request_(true)
{
}

Object::~Object()
{
}



const Mtx4* Object::getTransformMatrix() {

    if (calc_request_) {
        calc_request_ = false;
        makeTransformMatrix();
    }

    return &transform_;
}


void Object::makeTransformMatrix()
{
    Mtx4 s;
    s.scale(scale_);
    
    Mtx4 r;
    r.rotate(rotation_);
    
    Mtx4 t;
    t.translate(position_);


    transform_ = s * r * t;
}


}   // namespace theater
}   // namespace t3