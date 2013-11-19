// -*- mode:c++; coding:utf-8 -*-

#include "tri_camera.hpp"
#include "math/tri_math_util.hpp"



namespace t3 {
inline namespace gfx {


Camera::Camera()
    : position_( 0, 0, 0 )
    , target_( 0, 0, -1 )
    , fov_( toRadian( 35.0f ) )
    , up_( 0, 1, 0 )
    , front_( 0, 0, -1 )
    , right_( 1, 0, 0 )
    , recalculation_request_( false )
{
    calculateDirection();
}

Camera::~Camera()
{
}

void Camera::calculateDirection()
{

    //  右方向ベクトル計算
    front_ = target_ - position_;
    if ( !isZeroFloat( front_.x_ ) || !isZeroFloat( front_.z_ ) ){
        const Vec3 axis_y( 0, 1, 0 );
        Vec3::getCrossProduct( right_, front_, axis_y );
    }
    else {
        const Vec3 axis_z( 0, 0, 1 );
        Vec3::getCrossProduct( right_, front_, axis_z );
    }

    right_.normalize();

    //  上方向ベクトル計算
    Vec3::getCrossProduct( up_, right_, front_ );
    up_.normalize();

    //  前方向ベクトル計算
    front_.normalize();
}

void Camera::recalculate()
{
    if ( recalculation_request_ ){
        //  各方向ベクトルを再計算
        calculateDirection();
        calculateFrustum();
        calculateMatrix();

        recalculation_request_ = false;
    }
}

void Camera::calculateFrustum()
{
    float aspect = 480/640;
    float near = 1.0f;
    float far = 10000.0f;

    frustum_.initializeFrustum(fov_,
        aspect,
        near,
        far,
        front_,
        right_,
        up_,
        position_
    );
}

void Camera::calculateMatrix()
{
    view_matrix_.lookat(position_, target_, up_);
}


const Mtx4* Camera::getViewMatrix()
{
    recalculate();
    return &view_matrix_;
}


}   // namespace gfx
}   // namespace nd

