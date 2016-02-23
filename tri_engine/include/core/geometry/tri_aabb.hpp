////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_aabb.hpp
    バウンディングボックスの定義.
*/

#ifndef TRI_AABB_HPP_INCLUDED
#define TRI_AABB_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../math/tri_vec3.hpp"

TRI_CORE_NS_BEGIN


///
/// バウンディングボックス
class AABB {
public:
    ///
    /// コンストラクタ.
    /// デフォルトでmin_,mix_はfloatの限界値で初期化される
    AABB()
        : min_(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max())
        , max_(
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min())
    {}
    
    ///
    /// コンストラクタ.
    /// 最小値、最大値指定
    AABB(
        const Position3D& min,    ///< 最小値
        const Position3D& max     ///< 最大値
    )   : min_(min)
        , max_(max)
    {}
    
    ///
    ///  デストラクタ
    ~AABB()
    {}
    
public:
    ///
    /// AABBの拡張.
    /// 受け取った座標を含む大きさに拡張する
    void margePoint(
        const Position3D& p   ///< 座標
    ) {
        //  x軸
        if (min_.x_ > p.x_) {
            min_.x_ = p.x_;
        } else if (max_.x_ < p.x_) {
            max_.x_ = p.x_;
        }
        
        //  y軸
        if (min_.y_ > p.y_) {
            min_.y_ = p.y_;
        } else if (max_.y_ < p.y_) {
            max_.y_ = p.y_;
        }
        
        //  z軸
        if (min_.z_ > p.z_) {
            min_.z_ = p.z_;
        } else if (max_.z_ < p.z_) {
            max_.z_ = p.z_;
        }
    }
    
    ///
    /// AABBの拡張.
    /// AABB同士のマージ
    void marge(
        const AABB& aabb
    ) {
        margePoint(aabb.max_);
        margePoint(aabb.min_);
    }
    
    ///
    /// 最小値設定.
    void min(
        const Position3D& min ///< 最小値
    ) {
        min_ = min;
    }

    ///
    /// 最小値取得.
    const Position3D& min() const {
        return min_;
    }
    
    /// 
    /// 最大値設定.
    void max(
        const Position3D& max ///< 最大値
    ) {
        max_ = max;
    }
    
    ///
    /// 最大値取得.
    /// @return 最大値
    const Position3D& max() const {
        return max_;
    }
    
    ///
    /// 点がAABBの内側か判定
    /// @retval true 内側
    /// @retval false 外側
    bool isInside(
        const Position3D& p   ///< 判定する点
    ) const {
        //  x
        if (p.x_ > max_.x_) {
            return false;
        }
        if (p.x_ < min_.x_) {
            return false;
        }
        
        //  y
        if (p.y_ > max_.y_) {
            return false;
        }
        if (p.y_ < min_.y_) {
            return false;
        }
        
        //  z
        if (p.z_ > max_.z_) {
            return false;
        }
        if (p.z_ < min_.z_) {
            return false;
        }
        
        return true;
    }

    /// 中心点取得.
    Position3D center() const {
        return (min_ + max_) * 0.5f;
    }
    
    ///
    /// 半径取得.
    Vec3 radius() const {
        return (max_ - min_) * 0.5f;
    }


private:
    Position3D min_;          ///< 最小値
    Position3D max_;          ///< 最大値

};



TRI_CORE_NS_END

#endif  // TRI_AABB_HPP_INCLUDED
