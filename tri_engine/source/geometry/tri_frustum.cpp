//
//  tri_frustum.cpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/06/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "geometry/tri_frustum.hpp"
#include <cmath>



namespace t3 {
inline namespace geometry {


Frustum::Frustum()
    : fov_(toDegree(45.0f))
    , aspect_(400.0f / 240.0f)
    , near_(1.0f)
    , far_(10000.0f)
{

}


Frustum::~Frustum()
{
}

void Frustum::initializeFrustum(
    float fov,
    float aspect,
    float near,
    float far,
    const Vec3& front,
    const Vec3& right,
    const Vec3& up,
    const Vec3& pos
){
    fov_ = fov;
    aspect_ = aspect;
    near_ = near;
    far_ = far;
    pos_ = pos;


    float tan_fov_over2 = std::tan(fov/2.0f);

    Vec3 near_right = (near * tan_fov_over2) * aspect * right;
    Vec3 far_right = (far * tan_fov_over2) * aspect * right;
    Vec3 near_up = (near * tan_fov_over2 ) * up;
    Vec3 far_up = (far * tan_fov_over2)  * up;

    near_clip_[0] = ((near * front) - near_right + near_up) + pos;
    near_clip_[1] = ((near * front) + near_right + near_up) + pos;
    near_clip_[2] = ((near * front) + near_right - near_up) + pos;
    near_clip_[3] = ((near * front) - near_right - near_up) + pos;

    far_clip_[0] = ((far * front) - far_right + far_up) + pos;
    far_clip_[1] = ((far * front) + far_right + far_up) + pos;
    far_clip_[2] = ((far * front) + far_right - far_up) + pos;
    far_clip_[3] = ((far * front) - far_right - far_up) + pos;

    plane_[SIDE_NEAR] = Plane(near_clip_[2], near_clip_[1], near_clip_[0]);
    plane_[SIDE_FAR] = Plane(far_clip_[0], far_clip_[1], far_clip_[2]);
    plane_[SIDE_RIGHT] = Plane(far_clip_[2], far_clip_[1], pos);
    plane_[SIDE_TOP] = Plane(far_clip_[1], far_clip_[0], pos);
    plane_[SIDE_LEFT] = Plane(far_clip_[0], far_clip_[3], pos);
    plane_[SIDE_BOTTOM] = Plane(far_clip_[3], far_clip_[2], pos);

}


bool Frustum::isInside(
    const Vec3& point
){
    for(int i = 0; i < SIDE_NUM; ++i){
        if(!plane_[i].isInside(point)){
            return false;
        }
    }
    return true;
}

bool Frustum::isInSide(
    const Vec3& point,
	float radius
){
	// test
	const Vec3 dist = pos_ - point;
	if(dist.lengthSquare() <= radius * radius){
		return true;
	}

	// check
	for(int i = 0; i < SIDE_NUM; ++i){
        if(!plane_[i].isInside(point, radius)){
            return false;
        }
    }
	return true ;
}



}   // namespace geometry
}   // namespace t3


