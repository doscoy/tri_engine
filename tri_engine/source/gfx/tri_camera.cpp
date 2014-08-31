#include "kernel/memory/tri_new.hpp"
#include "gfx/tri_camera.hpp"
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

CameraPtr Camera::create() {

    std::shared_ptr<Camera> cam(T3_NEW Camera);
    return cam;
}


void Camera::calculateDirection()
{

    //  右方向ベクトル計算
    front_ = target_ - position_;
    if ( !isZeroFloat( front_.x_ ) || !isZeroFloat( front_.z_ ) ){
        right_ = Vec3::crossProduct(front_, Vec3::axisY());
    }
    else {
         right_ = Vec3::crossProduct(front_, Vec3::axisZ());
    }

    right_.normalize();

    //  上方向ベクトル計算
    up_ = Vec3::crossProduct(right_, front_);
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


const Mtx44* Camera::viewMatrix()
{
    recalculate();
    return &view_matrix_;
}


}   // namespace gfx
}   // namespace nd

