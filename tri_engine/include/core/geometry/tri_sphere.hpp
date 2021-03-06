////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_sphere.hpp
    球.
*/
#ifndef TRI_SPHERE_HPP_INCLUDED
#define TRI_SPHERE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_vec3.hpp"

TRI_CORE_NS_BEGIN


///
/// 球プリミティブ
class Sphere {
public:
    ///
    /// コンストラクタ
    Sphere() = default;
    
    ///
    /// コンストラクタ
    Sphere(
        const Vec3& position,   ///< 座標
        const float radius      ///< 半径
    )   : position_(position)
        , radius_(radius)
    
    {}
    
    ///
    /// デストラクタ
    ~Sphere() = default;
    
public:
    ///
    /// 半径を設定
    void radius(
        const float radius  ///< 半径
    ) {
        radius_ = radius;
    }

    ///
    /// 半径を取得
    float radius() const {
        return radius_;
    }
    
    ///
    /// 半径の二乗を取得
    float getRadiusSq() const {
        return radius_ * radius_;
    }
    
    ///
    /// 座標を設定
    void position(
        const Vec3& position    ///< 座標
    ) {
        position_ = position;
    }
    
    ///
    /// 座標を取得
    const Vec3& position() const {
        return position_;
    }
    
private:

    ///
    /// 座標
    Vec3 position_;
    
    ///
    /// 半径
    float radius_;

};

TRI_CORE_NS_END

#endif  // TRI_SPHERE_HPP_INCLUDED
