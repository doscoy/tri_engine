

#include "gfx/tri_camera_updater.hpp"
#include "math/tri_math_util.hpp"
#include "gfx/tri_camera.hpp"



namespace t3 {


LookAtCameraUpdater::LookAtCameraUpdater()
{
}


LookAtCameraUpdater::~LookAtCameraUpdater()
{
}

void LookAtCameraUpdater::position(const Vec3 &v)
{
    camera()->position(v);
}

void LookAtCameraUpdater::position(
    const float x,
    const float y,
    const float z
) {
    position(Vec3(x, y, z));
}


void LookAtCameraUpdater::targetPosition(const Vec3 &v)
{
    camera()->targetPosition(v);
}

void LookAtCameraUpdater::targetPosition(
    const float x,
    const float y,
    const float z
) {
    targetPosition(Vec3(x, y, z));
}

void LookAtCameraUpdater::dollyX(
    const float speed
){
    const Vec3* right = camera()->rightVector();

    //  左右にドリーする
    dolly(*right, speed);
}

void LookAtCameraUpdater::dollyY(
    const float speed
){
    const Vec3* up = camera()->upVector();

    //  上下にドリーする
    dolly(*up, speed);
}

void LookAtCameraUpdater::dollyZ(
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
    Vec3 pos = *cam->position();
    Vec3 tar = *cam->targetPosition();

    pos += (dir * speed);
    tar += (dir * speed);
    
    cam->position(pos);
    cam->targetPosition(tar);
}


void LookAtCameraUpdater::panV(
    const float speed
){
    const Vec3* right = camera()->rightVector();

    //  上下にパン
    pan(*right, toRadian(speed));
}

void LookAtCameraUpdater::panH(
    const float speed
){
    const Vec3* up = camera()->upVector();

    //  左右にパン
    pan(*up, toRadian(speed));
}

//-----------------------------------------------------------------------------
void
LookAtCameraUpdater::pan(
    const Vec3& axis,
    const float speed
){
    CameraPtr cam = camera();
    
    Vec3 dir = *cam->targetPosition() - *cam->position();

    Mtx44 mtx;
    Mtx44::makeRotateAxis(mtx, axis, speed);

    Vec3 a = mtx.xform(dir);
    cam->targetPosition( *cam->position() + a );

}


}   // namespace nd
