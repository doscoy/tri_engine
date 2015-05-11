/**
    @file tri_camera_updater.hpp
    カメラ操作.
*/

#ifndef TRI_CAMERA_UPDATER_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_HPP_INCLUDED

//  include
#include "../math/tri_math.hpp"
#include "tri_camera.hpp"
#include "base/tri_std.hpp"


namespace t3 {


///
/// カメラ操作
class CameraUpdater
{
public:
    ///
    /// コンストラクタ
    CameraUpdater(){}


    ///
    /// デストラクタ
    virtual ~CameraUpdater(){}

public:
    ///
    /// 管理するカメラ設定
    void camera(
        SharedPtr<Camera> camera
    ) {
        camera_ = camera;
    }
    
protected:
    ///
    /// 管理するカメラ取得
    CameraPtr camera() {
        return camera_;
    }
    
private:
    CameraPtr camera_;  ///< 管理しているカメラ
};


///
/// 位置・注視点による制御
///
class LookAtCameraUpdater
    : public CameraUpdater
{
public:
    ///
    /// コンストラクタ
    LookAtCameraUpdater();

    ///
    /// デストラクタ
    virtual ~LookAtCameraUpdater();


public:
    ///
    /// 座標設定
    void position(const Vec3& v);

    ///
    /// 座標設定
    void position(float x, float y, float z);

    ///
    /// 注視点設定
    void targetPosition(const Vec3& v);

    /// 
    /// 注視点設定
    void targetPosition(float x, float y, float z);

    ///
    /// x軸ドリー
    void dollyX( 
        const float speed ///< 速度
    );

    ///
    /// y軸ドリー
    void dollyY( 
        const float speed ///< 速度
    );

    ///
    /// z軸ドリー
    void dollyZ( 
        const float speed ///< 速度
    );

    ///
    /// 任意方向ドリー
    void dolly(
        const Vec3& dir,    ///< 方向
        const float speed   ///< 速度
    );

    ///
    /// 縦首振り
    void panV( const float speed );

    ///
    /// 横首振り
    void panH( const float speed );

    ///
    /// 任意軸首振り
    void pan(
        const Vec3& axis,   ///< 軸
        const float speed   ///< 速度
    );
    

private:


};


}   // namespace t3

#endif // TRI_CAMERA_UPDATER_HPP_INCLUDED
