////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_camera_updater.hpp
    カメラ操作.
*/

#ifndef TRI_CAMERA_UPDATER_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_math.hpp"
#include "tri_camera.hpp"
#include "core/base/tri_task.hpp"

TRI_CORE_NS_BEGIN



///
/// カメラ操作
class CameraUpdater
    : public TaskBase
{
public:
    ///
    /// コンストラクタ
    CameraUpdater()
        : TaskBase()
        , camera_(Camera::create())
    {}


    ///
    /// デストラクタ
    virtual ~CameraUpdater()
    {}

public:
    ///
    /// 管理するカメラ設定
    void camera(
        CameraPtr camera
    ) {
        camera_ = camera;
    }
    
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
    void position(const Position3D& v);

    ///
    /// 座標設定
    void position(float x, float y, float z);

    ///
    /// 注視点設定
    void targetPosition(const Position3D& v);

    /// 
    /// 注視点設定
    void targetPosition(float x, float y, float z);

    ///
    /// 水平ドリー
    void dollyH( 
        const float speed ///< 速度
    );

    ///
    /// 垂直ドリー
    void dollyV( 
        const float speed ///< 速度
    );

    ///
    /// 前後ドリー
    void dollyFront( 
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
    void panV(const Degree angle);

    ///
    /// 横首振り
    void panH(const Degree angle);

    ///
    /// 任意軸首振り
    void pan(
        const Vec3& axis,   ///< 軸
        const Degree angle  ///< 角速度
    );
    
    ///
    /// タスク更新
    void onTaskUpdate(
        const FrameInfo& frame_info
    ) override {}

private:


};
using LookAtCameraUpdaterPtr = SharedPtr<LookAtCameraUpdater>;




///
/// カメラ操作
class RotateCameraUpdater     
    : public CameraUpdater
{
public:
    RotateCameraUpdater();
    virtual ~RotateCameraUpdater();


public:
    ///
    /// 姿勢設定
    void setup(
        Position3D center,
        Rotation rotate,
        float distance
    ) {
        center_ = center;
        rotate_ = rotate;
        distance_ = distance;
    }

    ///
    /// x軸（縦）回転 
    void rollV(
        float speed ///< 移動量
    ) {
        rotate_.addX(speed);
    }

    ///
    /// y軸（横）回転
    void rollH(
        float speed ///< 移動量
    ) {
        rotate_.addY(speed);
    }


    ///
    /// 中心点を取得
    const Position3D& center() const {
        return center_;
    }

    ///
    /// 中心点を設定
    void center(
        const Position3D& pos
    ) {
        center_ = pos;
    }

    ///
    /// 距離を設定
    void distance(float distance) {
        distance_ = distance;
    }
    
    ///
    /// 距離を取得
    float distance() const {
        return distance_;
    }

    ///
    /// タスク更新
    void onTaskUpdate(
        const FrameInfo& frame_info
    ) override;

private:
    ///
    /// X軸ロール
    void onRollV(
        const t3::EventPtr event
    );
    
    ///
    /// Y軸ロール
    void onRollH(
        const t3::EventPtr event
    );
    

private:
    Position3D center_;
    Rotation rotate_;
    float distance_;
};

using RotateCameraUpdaterPtr = SharedPtr<RotateCameraUpdater>;



TRI_CORE_NS_END

#endif // TRI_CAMERA_UPDATER_HPP_INCLUDED
