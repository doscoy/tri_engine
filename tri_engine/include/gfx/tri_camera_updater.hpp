#ifndef TRI_CAMERA_UPDATER_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_HPP_INCLUDED


#include "../math/tri_math.hpp"
#include <memory>

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
        std::shared_ptr<Camera> camera
    ) {
        camera_ = camera;
    }
    
protected:
    std::shared_ptr<Camera> getManagedCamera() {
        return camera_;
    }
    
private:
    std::shared_ptr<Camera> camera_;
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
