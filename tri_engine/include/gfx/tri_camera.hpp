#ifndef TRI_CAMERA_HPP_INCLUDED
#define TRI_CAMERA_HPP_INCLUDED


//  include
#include "math/tri_math_types.hpp"
#include "math/tri_matrix.hpp"
#include "../geometry/tri_frustum.hpp"
#include "tri_entity.hpp"
#include "base/tri_std.hpp"


namespace t3 {

// 前方宣言
class Camera;

/// カメラポインタ
using CameraPtr = SharedPtr<Camera>;

///
/// カメラ
class Camera
    : public Entity
{
public:
    ///
    /// デストラクタ
    ~Camera();
    
    ///
    /// 生成関数
    static CameraPtr create();
    
private:
    ///
    /// コンストラクタ.
    /// 生成関数経由でしか作れない
    Camera();
    
public:
    ///
    /// カメラ行列取得.
    const Mtx44* viewMatrix();
    
    ///
    /// 位置設定.
    void position(
        const Vec3& pos
    ) {
        position_ = pos;
        recalculation_request_ = true;
    }

    ///
    /// 位置取得.
    const Vec3* position() const {
        return &position_;
    }

    ///
    /// 注視点設定.
    void targetPosition(
        const Vec3& pos
    ) {
        target_ = pos;
        recalculation_request_ = true;
    }
    
    ///
    /// 注視点取得
    const Vec3* targetPosition() const {
        return &target_;
    }
    
    ///
    /// 上方向ベクトル取得
    const Vec3* upVector() const {
        return &up_;
    }
    
    ///
    /// 右方向ベクトル取得
    const Vec3* rightVector() const {
        return &right_;
    }
    
    ///
    /// 前方向ベクトル取得
    const Vec3* frontVector() const {
        return &front_;
    }
    
    
    ///
    /// 視野角設定
    void fieldOfView( 
        const float fov     ///< 視野角
    ) {
        fov_ = fov;
    }

    ///
    /// 視錐台取得
    const Frustum* frustum() const {
        return &frustum_;
    }

private:
    ///
    /// 行列計算
    void calculateMatrix();

    ///
    /// 視錐台計算
    void calculateFrustum();

    ///
    /// 方向計算
    void calculateDirection();

    ///
    /// 全て再計算
    void recalculate();

private:
    Vec3 position_;   ///< カメラ座標
    Vec3 target_;     ///< 注視点
    float fov_;       ///< 視野角
    Vec3 up_;         ///< 上方向ベクトル
    Vec3 front_;      ///< 前方向ベクトル
    Vec3 right_;      ///< 右方向ベクトル

    Mtx44 view_matrix_; ///< カメラ行列
    Frustum frustum_;   ///< 視錐台

                        //  フラグ
    bool recalculation_request_;    ///< 方向ベクトル再計算フラグ

};  // class Camera


}   // namespace t3

#endif // TRI_CAMERA_HPP_INCLUDED
