// -*- mode:c++; coding:utf-8 -*-

#include "tri_camera_updater.hpp"
#include "math/tri_math_util.hpp"
#include "tri_camera.hpp"



namespace t3 {
inline namespace gfx {

LookAtCameraUpdater::LookAtCameraUpdater()
{
}


LookAtCameraUpdater::~LookAtCameraUpdater()
{
}

void LookAtCameraUpdater::position(const Vec3 &v)
{
    getManagedCamera()->position(v);
}

void LookAtCameraUpdater::position(
    const float x,
    const float y,
    const float z
) {
    position(Vec3(x, y, z));
}


void LookAtCameraUpdater::setTargetPosition(const Vec3 &v)
{
    getManagedCamera()->setTargetPosition(v);
}

void LookAtCameraUpdater::setTargetPosition(
    const float x,
    const float y,
    const float z
) {
    setTargetPosition(Vec3(x, y, z));
}

void LookAtCameraUpdater::dollyX(
    const float speed
){
    const Vec3* right = getManagedCamera()->getRightVector();

    //  左右にドリーする
    dolly(*right, speed);
}

void LookAtCameraUpdater::dollyY(
    const float speed
){
    const Vec3* up = getManagedCamera()->getUpVector();

    //  上下にドリーする
    dolly(*up, speed);
}

void LookAtCameraUpdater::dollyZ(
    const float speed
){
    const Vec3* front = getManagedCamera()->getFrontVector();

    //  前後にドリーする
    dolly(*front, speed);
}

void LookAtCameraUpdater::dolly(
    const Vec3& dir,
    const float speed
){
    std::shared_ptr<Camera> cam = getManagedCamera();
    Vec3 pos = *cam->position();
    Vec3 tar = *cam->getTargetPosition();

    pos += (dir * speed);
    tar += (dir * speed);
    
    cam->position(pos);
    cam->setTargetPosition(tar);
}


void LookAtCameraUpdater::panV(
    const float speed
){
    const Vec3* right = getManagedCamera()->getRightVector();

    //  上下にパン
    pan(*right, toRadian(speed));
}

void LookAtCameraUpdater::panH(
    const float speed
){
    const Vec3* up = getManagedCamera()->getUpVector();

    //  左右にパン
    pan(*up, toRadian(speed));
}

//-----------------------------------------------------------------------------
void
LookAtCameraUpdater::pan(
    const Vec3& axis,
    const float speed
){
    std::shared_ptr<Camera> cam = getManagedCamera();
    
    Vec3 dir = *cam->getTargetPosition() - *cam->position();

    Mtx44 mtx;
    Mtx44::makeRotateAxis(mtx, axis, speed);

    Vec3 a = mtx.xform(dir);
    cam->setTargetPosition( *cam->position() + a );

}




}   // namespace gfx
}   // namespace nd
