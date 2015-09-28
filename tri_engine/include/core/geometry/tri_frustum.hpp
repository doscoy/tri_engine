////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_frustum.hpp
    フラスタム.
*/

#ifndef TRI_FRUSTUM_HPP_INCLUDED
#define TRI_FRUSTUM_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "../math/tri_vec3.hpp"
#include "tri_plane.hpp"

TRI_CORE_NS_BEGIN



///
/// フラスタム
class Frustum {
public:
    ///
    /// コンストラクタ
    Frustum();

    ///
    /// デストラクタ
    ~Frustum();

public:
    ///
    /// 面タイプ
    enum Side {
        SIDE_NEAR,      ///< 手前
        SIDE_FAR,       ///< 奥
        SIDE_TOP,       ///< 上
        SIDE_RIGHT,     ///< 右
        SIDE_BOTTOM,    ///< 下
        SIDE_LEFT,      ///< 左
        
        SIDE_NUM        ///< 面総数
    };


public:
    ///
    /// 視野角を設定
    void setFov(float fov){
        fov_ = fov;
    }

    ///
    /// アスペクト比を設定
    void setAspect(float aspect){
        aspect_ = aspect;
    }

    ///
    /// ニアクリップ面を設定
    void setNear(float near){
        near_ = near;
    }

    ///
    /// ファークリップ面を設定
    void setFar(float far){
        far_ = far;
    }

    ///
    /// フラスタム初期化
    void initializeFrustum(
        float fov,          ///< 視野角
        float aspect,       ///< アスペクト比
        float near,         ///< ニアクリップ
        float far,          ///< ファークリップ
        const Vec3& front,  ///< 前ベクトル
        const Vec3& right,  ///< 右ベクトル
        const Vec3& up,     ///< 上ベクトル
        const Vec3& pos     ///< 位置
    );

    ///
    /// 面を構成する平面取得
    const Plane* getPlane(
        int side    ///< 面タイプ
    ) const {
        return &plane_[side];
    }

    ///
    /// 内側判定
    bool isInside(
        const Vec3& point   ///< 位置
    );

    ///
    /// 内側判定.
    /// 位置と半径
    bool isInSide(
		const Vec3& point,  ///< 位置
		float radius        ///< 半径
    );

private:
    Plane plane_[SIDE_NUM];     ///< フラスタムを構成する各面
    Vec3 near_clip_[4];         ///< 手前の面座標
    Vec3 far_clip_[4];          ///< 奥の面座標
    Vec3 pos_;                  ///< 位置
    float fov_;                 ///< 視野角
    float aspect_;              ///< アスペクト比
    float near_;                ///< 前面オフセット
    float far_;                 ///< 奥面オフセット
 
};


TRI_CORE_NS_END


#endif  // TRI_FRUSTUM_HPP_INCLUDED
