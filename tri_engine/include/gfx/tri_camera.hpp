#ifndef TRI_CAMERA_HPP_INCLUDED
#define TRI_CAMERA_HPP_INCLUDED

#include "math/tri_math_types.hpp"
#include "math/tri_interpolation.hpp"
#include "math/tri_matrix.hpp"
#include "../geometry/tri_frustum.hpp"
#include "tri_entity.hpp"



namespace t3 {
inline namespace gfx {

class Camera
    : public Entity
{
public:
    Camera();
    ~Camera();
    
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
    const Mtx44* getViewMatrix();
    
    void position(
        const Vec3& pos
    ) {
        position_ = pos;
        recalculation_request_ = true;
    }

    const Vec3* position() const {
        return &position_;
    }

    void setTargetPosition(
        const Vec3& pos
    ) {
        target_ = pos;
        recalculation_request_ = true;
    }
    
    const Vec3* getTargetPosition() const {
        return &target_;
    }
    
    const Vec3* getUpVector() const {
        return &up_;
    }
    
    const Vec3* getRightVector() const {
        return &right_;
    }
    
    const Vec3* getFrontVector() const {
        return &front_;
    }
    
    
    void    setFieldOfView( const float fov ) {
        fov_ = fov;
    }

    const Frustum* getFrustom() const {
        return &frustum_;
    }

private:
    void calculateMatrix();
    void calculateFrustum();

    void calculateDirection();
    void recalculate();

};  // class Camera

using CameraPtr = std::shared_ptr<Camera>;


}   // namespace gfx
}   // namespace t3

#endif // TRI_CAMERA_HPP_INCLUDED
