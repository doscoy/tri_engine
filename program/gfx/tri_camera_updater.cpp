// -*- mode:c++; coding:utf-8 -*-

#include "tri_camera_updater.hpp"
#include "math/tri_math_util.hpp"
#include "tri_camera.hpp"

namespace {
const float SHAKE_TIMING = 0.02f;
}


namespace t3 {
inline namespace gfx {

LookAtCameraUpdater::LookAtCameraUpdater()
{
}


LookAtCameraUpdater::~LookAtCameraUpdater()
{
}

void LookAtCameraUpdater::setPosition(const Vec3 &v)
{
    getManagedCamera()->setPosition(v);
}

void LookAtCameraUpdater::setPosition(
    const float x,
    const float y,
    const float z
) {
    setPosition(Vec3(x, y, z));
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
    Camera* cam = getManagedCamera();
    Vec3 pos = *cam->getPosition();
    Vec3 tar = *cam->getTargetPosition();

    pos += (dir * speed);
    tar += (dir * speed);
    
    cam->setPosition(pos);
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
//    Vec3 dir = target_ - position_;
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




}   // namespace gfx
}   // namespace nd
