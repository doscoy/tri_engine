#ifndef TRI_CAMERA_HPP_INCLUDED
#define TRI_CAMERA_HPP_INCLUDED

#include "math/tri_math_types.hpp"
#include "math/tri_interpolation.hpp"
#include "math/tri_matrix.hpp"

namespace t3
{

class Camera
{
private:
    //  基本パラメータ
    vec3_t position_;   // カメラ座標
    vec3_t target_;     // 注視点
    float fov_;         // 視野角
    float twist_;       // 注視点方向ひねり角

    vec3_t up_;         // 上方向ベクトル
    vec3_t front_;      // 前方向ベクトル
    vec3_t right_;      // 右方向ベクトル

    //  補間移動パラメータ
    Interpolation<vec3_t> position_updater_;    // 座標移動
    Interpolation<vec3_t> target_updater_;      // 注視点移動
    Interpolation<float> fov_updater_;          // 注視点移動


    mtx4_t view_matrix_;

    //  画面揺らしパラメータ
    float shake_time_;
    float now_shake_time_;
    float shake_interval_;
    float shake_power_;

    //  フラグ
    bool recalculation_request_;    ///< 方向ベクトル再計算フラグ

public:
    Camera();
    Camera( const vec3_t& pos, const vec3_t& target, const float fov );
    virtual ~Camera();

public:
    void getViewMatrix( mtx4_t& mtx ) const;


    void updateCamera(
        const tick_t tick
    );
    
    void setPosition(
        const float x,
        const float y,
        const float z
    );

    void setPosition(
        const vec3_t& pos
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

    const vec3_t& getPosition() const;

    void setTargetPosition(
        const float x,
        const float y,
        const float z
    );

    void setTargetPosition(
        const vec3_t& pos
    );

    const vec3_t& getTargetPosition() const;

    const vec3_t& getUpVector();

    vec3_t getShakedUpVector();

    const vec3_t& getRightVector();

    const vec3_t& getFrontVector();


    void    setFieldOfView( const float fov );
    
    float   getFieldOfView() const;

    void    setTwist( const float twist );
    
    float   getTwist() const;



    void    dollyX( const float speed );
    void    dollyY( const float speed );
    void    dollyZ( const float speed );
    void    dolly(
        const vec3_t& dir,
        const float speed
    );

    void    panV( const float speed );
    void    panH( const float speed );
    void    pan(
        const vec3_t& axis,
        const float speed
    );
    
    void    moveToPosition(
        const vec3_t& goal,
        const float sec,
        const InterpolationType type = INTERPOLATION_LINER
    );

    void    moveToTargetPosition(
        const vec3_t& goal,
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
        const vec3_t& pos,          ///< 座標
        const float ratio           ///< ブレンド比率
    );

    void    blendTargetPosition(
        const vec3_t& target,       ///< 注視点
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

private:

    void    calculateDirection();

    void    recalculateDirection();

};  // class Camera



//=============================================================================
}   // namespace t3

#endif // TRI_CAMERA_HPP_INCLUDED
