/**
    @file tri_plane.hpp
    平面プリミティブ.
*/

#ifndef TRI_PLANE_HPP_INCLUDED
#define TRI_PLANE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_math.hpp"


TRI_CORE_NS_BEGIN



///
/// 平面プリミティブ
class Plane {
public:
    ///
    /// コンストラクタ
    Plane() = default;

    ///
    /// コンストラクタ
    Plane(
        const Vec3& a,
        const Vec3& b,
        const Vec3& c
    ) {
        Vec3 ab = b - a;
        Vec3 ac = c - a;
        normal_ = ac.crossProduct(ab);
        normal_.normalize();
        point_ = a;
        dot_np_ = point_.dotProduct(normal_);
    }
    
    ///
    /// コンストラクタ
    Plane(
        const Vec3& point,
        const Vec3& normal
    )   : point_(point)
        , normal_(normal)
        , dot_np_(Vec3::dotProduct(point, normal))
    {}
    
    ///
    /// デストラクタ
    ~Plane() = default;

public:
    ///
    /// 座標が平面の内側にあるか判定
    bool isInside(
        const Vec3& pos ///< 座標
    ) const {
        Vec3 v = point_ - pos;
        float d = v.dotProduct(normal_);
        return d > 0;
    }
    
    ///
    /// 座標が平面の内側にあるか判定
    bool isInside(
        const Vec3& pos,    ///< 座標
        const float radius  ///< 半径
    ) {
        Vec3 d = normal_ * radius;
		Vec3 p = pos - d;
		return isInside(p);
    }
    
    ///
    /// 座標取得
    const Vec3& getPoint() const {
        return point_;
    }
    
    ///
    /// 法線取得
    const Vec3& getNormal() const {
        return normal_;
    }
    
    


public:
    ///
    /// 座標
    Vec3 point_;
    
    ///
    /// 法線
    Vec3 normal_;
    
    ///
    /// 平面方程式 Dot normal, position
    float dot_np_;
};

TRI_CORE_NS_END

#endif  // TRI_PLANE_HPP_INCLUDED
