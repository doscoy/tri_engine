#ifndef TRI_FRUSTUM_HPP_INCLUDED
#define TRI_FRUSTUM_HPP_INCLUDED


#include "../math/tri_vec3.hpp"
#include "tri_plane.hpp"

namespace t3 {



class Frustum
{
public:
    Frustum();
    ~Frustum();

public:
    enum Side {
        SIDE_NEAR,
        SIDE_FAR,
        SIDE_TOP,
        SIDE_RIGHT,
        SIDE_BOTTOM,
        SIDE_LEFT,
        
        SIDE_NUM
    };


public:
    void setFov(float fov){
        fov_ = fov;
    }

    void setAspect(float aspect){
        aspect_ = aspect;
    }

    void setNear(float near){
        near_ = near;
    }

    void setFar(float far){
        far_ = far;
    }

    void initializeFrustum(
        float fov,
        float aspect,
        float near,
        float far,
        const Vec3& front,
        const Vec3& right,
        const Vec3& up,
        const Vec3& pos
    );

    const Plane* getPlane(
        int side
    ) const {
        return &plane_[side];
    }

    bool isInside(
        const Vec3& point
    );

	bool isInSide(
		const Vec3& point,
		float radius
    );

private:
    Plane plane_[SIDE_NUM];
    Vec3 near_clip_[4];
    Vec3 far_clip_[4];
    Vec3 pos_;
    float fov_;
    float aspect_;
    float near_;
    float far_;

    
};


}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
