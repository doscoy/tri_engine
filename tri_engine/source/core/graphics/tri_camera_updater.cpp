////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_camera_updater.hpp"
#include "core/math/tri_math_util.hpp"
#include "core/graphics/tri_camera.hpp"
#include "core/graphics/tri_camera_updater_events.hpp"


TRI_CORE_NS_BEGIN



LookAtCameraUpdater::LookAtCameraUpdater()
    : CameraUpdater()
{
}


LookAtCameraUpdater::~LookAtCameraUpdater()
{
}

void LookAtCameraUpdater::position(
    const Position3D& v
) {
    camera()->position(v);
}

void LookAtCameraUpdater::position(
    const float x,
    const float y,
    const float z
) {
    position(Position3D(x, y, z));
}


void LookAtCameraUpdater::targetPosition(
    const Position3D& v
) {
    camera()->targetPosition(v);
}

void LookAtCameraUpdater::targetPosition(
    const float x,
    const float y,
    const float z
) {
    targetPosition(Position3D(x, y, z));
}

void LookAtCameraUpdater::dollyH(
    const float speed
){
    const Vec3* right = camera()->rightVector();

    //  左右にドリーする
    dolly(*right, speed);
}

void LookAtCameraUpdater::dollyV(
    const float speed
){
    const Vec3* up = camera()->upVector();

    //  上下にドリーする
    dolly(*up, speed);
}

void LookAtCameraUpdater::dollyFront(
    const float speed
){
    const Vec3* front = camera()->frontVector();

    //  前後にドリーする
    dolly(*front, speed);
}

void LookAtCameraUpdater::dolly(
    const Vec3& dir,
    const float speed
){
    CameraPtr cam = camera();
    Position3D pos = *cam->position();
    Position3D tar = *cam->targetPosition();
    pos += dir * speed;
    tar += dir * speed;
    
    cam->position(pos);
    cam->targetPosition(tar);
}


void LookAtCameraUpdater::panV(
    const Degree angle
){
    const Vec3* right = camera()->rightVector();

    //  上下にパン
    pan(*right, angle);
}

void LookAtCameraUpdater::panH(
    const Degree angle
){
    const Vec3* up = camera()->upVector();

    //  左右にパン
    pan(*up, angle);
}

//-----------------------------------------------------------------------------
void
LookAtCameraUpdater::pan(
    const Vec3& axis,
    const Degree angle
){
    CameraPtr cam = camera();
    
    Vec3 dir = *cam->targetPosition() - *cam->position();

    Mtx44 mtx;
    Mtx44::makeRotateAxis(mtx, axis, toRadian(angle));

    Vec3 a = mtx.xform(dir);
    cam->targetPosition( *cam->position() + a );

}



















////////////////////////////////////////////////////////////////////////////

RotateCameraUpdater::RotateCameraUpdater()
    : CameraUpdater()
    , center_(0, 0, 0)
    , rotate_(-20.0f, 0, 0)
    , distance_(50.0f)
{
    EventManager::addListener(this, &RotateCameraUpdater::onRollH, event::CameraRollH::TYPE);
    EventManager::addListener(this, &RotateCameraUpdater::onRollV, event::CameraRollV::TYPE);
}


RotateCameraUpdater::~RotateCameraUpdater() {
    EventManager::removeListener(this);
}


void RotateCameraUpdater::onTaskUpdate(
    const FrameInfo& frame_info
) {
    //  注視点設定
    camera()->targetPosition(center_);
    
    //  長さと回転からカメラ位置を決定
    Vec3 v(0,0,distance_);
    Mtx44 rot_mtx = Mtx44::getRotate(rotate_.x_, rotate_.y_, Degree(0));
    v = rot_mtx.xform(v);
    
    camera()->position(v);
}

void RotateCameraUpdater::onRollV(
    const t3::EventPtr event
) {
    const auto eve = static_cast<const event::CameraRollV*>(event.get());
    rollV(eve->speed());
}

void RotateCameraUpdater::onRollH(
    const t3::EventPtr event
) {
    const auto eve = static_cast<const event::CameraRollH*>(event.get());
    rollH(eve->speed());
}














TRI_CORE_NS_END
