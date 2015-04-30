#ifndef TRI_CAMERA_UPDATER_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_HPP_INCLUDED


#include "../math/tri_math.hpp"
#include "tri_camera.hpp"
#include "base/tri_std.hpp"


namespace t3 {



class CameraUpdater
{
public:
    CameraUpdater(){}
    virtual ~CameraUpdater(){}

public:
    void camera(
        SharedPtr<Camera> camera
    ) {
        camera_ = camera;
    }
    
protected:
    CameraPtr getManagedCamera() {
        return camera_;
    }
    
private:
    CameraPtr camera_;
};



class LookAtCameraUpdater
    : public CameraUpdater
{
public:
    LookAtCameraUpdater();
    virtual ~LookAtCameraUpdater();


public:
    void position(const Vec3& v);
    void position(float x, float y, float z);

    void targetPosition(const Vec3& v);
    void targetPosition(float x, float y, float z);

    void    dollyX( const float speed );
    void    dollyY( const float speed );
    void    dollyZ( const float speed );
    void    dolly(
        const Vec3& dir,
        const float speed
    );

    void    panV( const float speed );
    void    panH( const float speed );
    void    pan(
        const Vec3& axis,
        const float speed
    );
    

private:


};


}   // namespace t3

#endif // TRI_CAMERA_UPDATER_HPP_INCLUDED
