#ifndef TRI_CAMERA_HPP_INCLUDED
#define TRI_CAMERA_HPP_INCLUDED

#include "math/tri_math_types.hpp"
#include "math/tri_interpolation.hpp"
#include "math/tri_matrix.hpp"
#include "../geometry/tri_frustum.hpp"



namespace t3
{

class Camera
{
private:
    //  基本パラメータ
    Vec3 position_;   // カメラ座標
    Vec3 target_;     // 注視点
    float fov_;         // 視野角
    float twist_;       // 注視点方向ひねり角

    Vec3 up_;         // 上方向ベクトル
    Vec3 front_;      // 前方向ベクトル
    Vec3 right_;      // 右方向ベクトル

    Mtx4 view_matrix_;
    Frustum frustum_;

    //  補間移動パラメータ
    Interpolation<Vec3> position_updater_;    // 座標移動
    Interpolation<Vec3> target_updater_;      // 注視点移動
    Interpolation<float> fov_updater_;          // 注視点移動



    //  画面揺らしパラメータ
    float shake_time_;
    float now_shake_time_;
    float shake_interval_;
    float shake_power_;

    //  フラグ
    bool recalculation_request_;    ///< 方向ベクトル再計算フラグ

public:
    Camera();
    Camera( const Vec3& pos, const Vec3& target, const float fov );
    virtual ~Camera();

public:
    void getViewMatrix( Mtx4& mtx ) const;


    void updateCamera(
        const tick_t tick
    );
    
    void setPosition(
        const float x,
        const float y,
        const float z
    );

    void setPosition(
        const Vec3& pos
    );

    void setPositionX(
        const float val
    );
    void setPositionY(
        const float val
    );
    void setPositionZ(
        const float val
    );

    const Vec3& getPosition() const;

    void setTargetPosition(
        const float x,
        const float y,
        const float z
    );

    void setTargetPosition(
        const Vec3& pos
    );

    const Vec3& getTargetPosition() const;

    const Vec3& getUpVector();

    Vec3 getShakedUpVector();

    const Vec3& getRightVector();

    const Vec3& getFrontVector();


    void    setFieldOfView( const float fov );
    
    float   getFieldOfView() const;

    void    setTwist( const float twist );
    
    float   getTwist() const;



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
    
    void    moveToPosition(
        const Vec3& goal,
        const float sec,
        const InterpolationType type = INTERPOLATION_LINER
    );

    void    moveToTargetPosition(
        const Vec3& goal,
        const float sec,
        const InterpolationType type = INTERPOLATION_LINER
    );

    void    moveToFieldOfView(
        const float fov,
        const float sec,
        const InterpolationType type = INTERPOLATION_LINER
    );


    bool    isMovingPosition() const;

    bool    isMovingTargetPosition() const;

    bool    isMovingFieldOfView() const;

    

    void    shakeCamera(
        const float sec,            // 揺れ時間
        const float power           // 揺れパワー （ブルブルする角度）
    );

    bool    isShaking() const;


    void    blendPosition(
        const Vec3& pos,          ///< 座標
        const float ratio           ///< ブレンド比率
    );

    void    blendTargetPosition(
        const Vec3& target,       ///< 注視点
        const float ratio           ///< ブレンド比率
    );

    void    blendFieldOfView(
        const float fov,            ///< 視野角
        const float ratio           ///< ブレンド比率
    );


    void    blendCamera(
        const Camera& cam,          ///< カメラ
        const float ratio           ///< ブレンド比率
    );

    const Frustum* getFrustom() const {
        return &frustum_;
    }

private:
    void    calculateDirection();

    void    recalculateDirection();

};  // class Camera



//=============================================================================
}   // namespace t3

#endif // TRI_CAMERA_HPP_INCLUDED
