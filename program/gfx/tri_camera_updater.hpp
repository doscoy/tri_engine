#ifndef TRI_CAMERA_UPDATER_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_HPP_INCLUDED


#include "../math/tri_math.hpp"

namespace t3 {
inline namespace gfx {

class Camera;

class CameraUpdater
{
public:
    CameraUpdater(){}
    virtual ~CameraUpdater(){}

public:
    void setCamera(
        Camera* camera
    ) {
        camera_ = camera;
    }
    
protected:
    Camera* getManagedCamera() {
        return camera_;
    }
    
private:
    Camera* camera_;
};



class LookAtCameraUpdater
    : public CameraUpdater
{
public:
    LookAtCameraUpdater();
    virtual ~LookAtCameraUpdater();


public:
    void setPosition(const Vec3& v);
    void setPosition(float x, float y, float z);

    void setTargetPosition(const Vec3& v);
    void setTargetPosition(float x, float y, float z);

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


}   // namespace gfx
}   // namespace t3

#endif // TRI_CAMERA_UPDATER_HPP_INCLUDED
