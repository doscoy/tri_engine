#ifndef TRI_CAMERA_HPP_INCLUDED
#define TRI_CAMERA_HPP_INCLUDED

#include "math/tri_math_types.hpp"
#include "math/tri_interpolation.hpp"
#include "math/tri_matrix.hpp"
#include "../geometry/tri_frustum.hpp"
#include "tri_entity.hpp"
#include "base/tri_std.hpp"


namespace t3 {
inline namespace gfx {

class Camera;
using CameraPtr = SharedPtr<Camera>;

class Camera
    : public Entity
{
public:
    ~Camera();
    
    static CameraPtr create();
    
private:
    Camera();
    
private:
    //  基本パラメータ
    Vec3 position_;   // カメラ座標
    Vec3 target_;     // 注視点
    float fov_;         // 視野角

    Vec3 up_;         // 上方向ベクトル
    Vec3 front_;      // 前方向ベクトル
    Vec3 right_;      // 右方向ベクトル

    Mtx44 view_matrix_;
    Frustum frustum_;

    //  フラグ
    bool recalculation_request_;    ///< 方向ベクトル再計算フラグ

public:
    const Mtx44* viewMatrix();
    
    void position(
        const Vec3& pos
    ) {
        position_ = pos;
        recalculation_request_ = true;
    }

    const Vec3* position() const {
        return &position_;
    }

    void targetPosition(
        const Vec3& pos
    ) {
        target_ = pos;
        recalculation_request_ = true;
    }
    
    const Vec3* targetPosition() const {
        return &target_;
    }
    
    const Vec3* upVector() const {
        return &up_;
    }
    
    const Vec3* rightVector() const {
        return &right_;
    }
    
    const Vec3* frontVector() const {
        return &front_;
    }
    
    
    void    fieldOfView( const float fov ) {
        fov_ = fov;
    }

    const Frustum* frustum() const {
        return &frustum_;
    }

private:
    void calculateMatrix();
    void calculateFrustum();

    void calculateDirection();
    void recalculate();

};  // class Camera



}   // namespace gfx
}   // namespace t3

#endif // TRI_CAMERA_HPP_INCLUDED
