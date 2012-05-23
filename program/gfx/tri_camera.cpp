// -*- mode:c++; coding:utf-8 -*-

#include "tri_camera.hpp"
#include "math/tri_math_util.hpp"

namespace {
const float SHAKE_TIMING = 0.02f;
}


//=============================================================================
namespace t3
{


//=============================================================================

//-----------------------------------------------------------------------------
Camera::Camera()
    : position_( 0, 0, 0 )
    , target_( 0, 0, -1 )
    , fov_( toRadian( 35.0f ) )
    , twist_( 0.0f )
    , up_( 0, 1, 0 )
    , front_( 0, 0, -1 )
    , right_( 1, 0, 0 )
    , position_updater_()
    , target_updater_()
    , fov_updater_()
    , shake_time_( 0 )
    , now_shake_time_( 0 )
    , shake_power_( 0 )
    , recalculation_request_( false )
{
    calculateDirection();
}

//-----------------------------------------------------------------------------
Camera::Camera(
    const vec3_t& pos,
    const vec3_t& target,
    const float fov
)   : position_( pos )
    , target_( target )
    , fov_( fov )
    , twist_( 0.0f )
    , up_( 0, 1, 0 )
    , front_( 0, 0, -1 )
    , right_( 1, 0, 0 )
    , position_updater_()
    , target_updater_()
    , fov_updater_()
    , shake_time_( 0 )
    , now_shake_time_( 0 )
    , shake_interval_( 0 )
    , shake_power_( 0 )
    , recalculation_request_( false )
{
   calculateDirection();
}

//-----------------------------------------------------------------------------
Camera::~Camera()
{
}


//-----------------------------------------------------------------------------
void
Camera::updateCamera(
    const tick_t tick
){
    //  自動移動
    position_updater_.updateInterpolation( tick );
    target_updater_.updateInterpolation( tick );
    fov_updater_.updateInterpolation( tick );
}

//-----------------------------------------------------------------------------
void
Camera::setPosition(
    const float x,
    const float y,
    const float z
){
    position_.x = x;
    position_.y = y;
    position_.z = z;

    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
void
Camera::setPosition(
    const vec3_t& pos
){
    position_ = pos;
    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
void 
Camera::setPositionX(
    const float val
){
    position_.x = val;
    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
void 
Camera::setPositionY(
    const float val
){
    position_.y = val;
    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
void 
Camera::setPositionZ(
    const float val
){
    position_.z = val;
    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
const vec3_t&
Camera::getPosition() const {
    return position_;
}


//-----------------------------------------------------------------------------
void
Camera::setTargetPosition(
    const float x,
    const float y,
    const float z
){
    target_.x = x;
    target_.y = y;
    target_.z = z;

    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
void
Camera::setTargetPosition(
    const vec3_t& pos
){
    target_ = pos;
    recalculation_request_ = true;
}

//-----------------------------------------------------------------------------
const vec3_t&
Camera::getTargetPosition() const {
    return target_;
}

//-----------------------------------------------------------------------------
const vec3_t&
Camera::getUpVector() {
    recalculateDirection();
    return up_;
}


//-----------------------------------------------------------------------------
const vec3_t&
Camera::getRightVector() {
    recalculateDirection();
    return right_;
}

//-----------------------------------------------------------------------------
const vec3_t&
Camera::getFrontVector() {
    recalculateDirection();
    return front_;
}


//-----------------------------------------------------------------------------
void
Camera::setFieldOfView(
    const float fov
){
    fov_ = fov;
}

//-----------------------------------------------------------------------------
float
Camera::getFieldOfView() const {
    return fov_;
}


//-----------------------------------------------------------------------------
void
Camera::setTwist(
    const float twist
){
    recalculation_request_ = true;
    twist_ = twist;
}

//-----------------------------------------------------------------------------
float
Camera::getTwist() const {
    return twist_;
}


//-----------------------------------------------------------------------------
void
Camera::calculateDirection()
{

    //  右方向ベクトル計算
    front_ = target_ - position_;
    if ( !isZeroFloat( front_.x ) || !isZeroFloat( front_.z ) ){
        const vec3_t axis_y( 0, 1, 0 );
        vec3_t::getCrossProduct( right_, front_, axis_y );
    }
    else {
        const vec3_t axis_z( 0, 0, 1 );
        vec3_t::getCrossProduct( right_, front_, axis_z );
    }

    //  回転を反映
    if ( !isZeroFloat( twist_ ) ){
//        mtx44_t rotate;
//        nn::math::MTX44RotAxisRad_( &rotate, &front_, twist_ );
//        nn::math::VEC3TransformCoord( &right_, &rotate, &right_ );
    }
    right_.normalize();

    //  上方向ベクトル計算
    vec3_t::getCrossProduct( up_, right_, front_ );
    up_.normalize();

    //  前方向ベクトル計算
    front_.normalize();
}

//-----------------------------------------------------------------------------
void
Camera::recalculateDirection()
{
    if ( recalculation_request_ ){
        //  各方向ベクトルを再計算
        calculateDirection();
        recalculation_request_ = false;
    }
}

//-----------------------------------------------------------------------------
void
Camera::dollyX(
    const float speed
){
    recalculateDirection();

    //  左右にドリーする
    dolly( right_, speed );
}

//-----------------------------------------------------------------------------
void
Camera::dollyY(
    const float speed
){
    recalculateDirection();

    //  上下にドリーする
    dolly( up_, speed );
}

//-----------------------------------------------------------------------------
void
Camera::dollyZ(
    const float speed
){
    recalculateDirection();

    //  前後にドリーする
    dolly( front_, speed );
}

//-----------------------------------------------------------------------------
void
Camera::dolly(
    const vec3_t& dir,
    const float speed
){
    position_ += (dir * speed);
    target_ += (dir * speed);
}


//-----------------------------------------------------------------------------
void
Camera::panV(
    const float speed
){
    recalculateDirection();

    //  上下にパン
    pan( right_, toRadian( speed ) );
}

//-----------------------------------------------------------------------------
void
Camera::panH(
    const float speed
){
    recalculateDirection();

    //  左右にパン
    pan( up_, toRadian( speed ) );
}

//-----------------------------------------------------------------------------
void
Camera::pan(
    const vec3_t& axis,
    const float speed
){
    vec3_t dir = target_ - position_;
/*    
    mtx44_t mtx;
    nn::math::MTX34RotAxisRad(
        &mtx,
        &axis,
        speed
    );

    nn::math::VEC3TransformNormal(
        &dir,
        &mtx,
        &dir
    );

    setTargetPosition( position_ + dir );
*/
}

//-----------------------------------------------------------------------------
void
Camera::moveToPosition(
    const vec3_t& goal,
    const float sec,
    const InterpolationType type
){
    position_updater_.startInterpolation( position_, goal, sec, type );
}

//-----------------------------------------------------------------------------
void
Camera::moveToTargetPosition(
    const vec3_t& goal,
    const float sec,
    const InterpolationType type
){
    target_updater_.startInterpolation( target_, goal, sec, type );
}


//-----------------------------------------------------------------------------
void
Camera::moveToFieldOfView(
    const float goal,
    const float sec,
    const InterpolationType type
){
    fov_updater_.startInterpolation( fov_, goal, sec, type );
}

//-----------------------------------------------------------------------------
bool
Camera::isMovingPosition() const {
    return position_updater_.isActive();
}

//-----------------------------------------------------------------------------
bool
Camera::isMovingTargetPosition() const {
    return target_updater_.isActive();
}

//-----------------------------------------------------------------------------
bool
Camera::isMovingFieldOfView() const {
    return fov_updater_.isActive();
}


//-----------------------------------------------------------------------------
void
Camera::shakeCamera(
    const float sec,
    const float power
){
    shake_time_ = sec;
    now_shake_time_ = 0;
    shake_power_ = power;
}


//-----------------------------------------------------------------------------
bool
Camera::isShaking() const {
    return shake_time_ > 0;
}

//-----------------------------------------------------------------------------
void
Camera::blendPosition(
    const vec3_t& pos,
    const float ratio
){
    //  座標をブレンド
    vec3_t diff_pos = pos - position_;
    setPosition( position_ + (diff_pos * ratio) );
}

//-----------------------------------------------------------------------------
void
Camera::blendTargetPosition(
    const vec3_t& target,
    const float ratio
){
    //  注視点をブレンド
    vec3_t diff_target = target - target_;
    setTargetPosition( target_ + (diff_target * ratio) );
}

//-----------------------------------------------------------------------------
void
Camera::blendFieldOfView(
    const float fov,
    const float ratio
){
    //  視野角をブレンド
    float diff_fov = fov - fov_;
    fov_ += diff_fov * ratio;
}

//-----------------------------------------------------------------------------
void
Camera::blendCamera(
    const Camera& cam,
    const float ratio
){
    blendPosition( cam.position_, ratio );
    blendTargetPosition( cam.target_, ratio );
    blendFieldOfView( cam.fov_, ratio );
}

void Camera::getViewMatrix( mtx4_t& mtx ) const
{
    mtx.lookat( position_, target_, up_ );
}

//=============================================================================
}   // namespace nd
