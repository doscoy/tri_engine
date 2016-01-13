////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_transform.hpp
    姿勢制御.
*/

#ifndef TRI_TRANSFORM_HPP_INCLUDED
#define TRI_TRANSFORM_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/math/tri_vec3.hpp"
#include "core/base/tri_types.hpp"
#include "cross/cross_std.hpp"
#include "core/kernel/memory/tri_new.hpp"


TRI_CORE_NS_BEGIN

class Transform2D;
using Transform2DPtr = SharedPtr<Transform2D>;


///
/// 2次元姿勢制御クラス
class Transform2D final
    :  Uncopyable
{
    ///
    /// コンストラクタ
    Transform2D()
        : position_(0, 0)
        , rotation_(0, 0, 0)
        , scale_(1.0f, 1.0f)
        , parent_(nullptr)
    {}
public:
    
    ///
    /// デストラクタ
    ~Transform2D() = default;

public:
    ///
    /// 座標を取得
    Vec2& position() {
        return position_;
    }
    
    ///
    /// 座標を取得
    const Vec2& position() const {
        return position_;
    }
    
    ///
    /// 座標を設定
    void position(
        const Vec2& pos
    ) {
        position_ = pos;
    }
    
    ///
    /// 座標を設定
    void position(
        const float x,
        const float y
    ) {
        position_.x_ = x;
        position_.y_ = y;
    }
    
    ///
    ///  回転情報を取得
    Vec3& rotation() {
        return rotation_;
    }
    
    ///
    /// 回転情報を取得
    const Vec3& rotation() const {
        return rotation_;
    }
    
    ///
    /// 回転情報を設定
    void rotation(
        const Vec3& rot
    ) {
        rotation_ = rot;
    }
    
    ///
    ///  スケールを取得
    Vec2& scale() {
        return scale_;
    }
    
    ///
    /// スケールを取得
    const Vec2& scale() const {
        return scale_;
    }
    
    ///
    /// スケールを設定
    void scale(
        const Vec2& scale
    ) {
        scale_ = scale;
    }
    
    ///
    /// スケールを設定
    void scale(
       const float x,
       const float y
    ) {
        scale_.x_ = x;
        scale_.y_ = y;
    }

    ///
    /// スケールを設定
    void scale(
        const float s
    ) {
        scale_.x_ = s;
        scale_.y_ = s;
    }

    ///
    /// 親の姿勢を設定
    void parent(
        Transform2DPtr p
    ) {
        parent_ = p;
    }
    
    ///
    /// 親の姿勢があるか取得
    bool hasParent() const {
        return parent_ != nullptr;
    }
    
    ///
    /// 親情報を取得
    Transform2DPtr parent() {
        return parent_;
    }
    
    ///
    /// 親情報を取得
    const Transform2DPtr parent() const {
        return parent_;
    }

    ///
    /// 階層構造を加味した座標を取得
    t3::Vec2 globalPosition() const {
        if (!hasParent()) {
            //  親が居ないのでただ座標を返す
            return position_;
        }
        
        //  親が居る
        //  親の情報と掛けあわせてグローバル座標を計算
        
        
        //  親の回転の影響を受けた座標
        float parent_rotate = toRadian(parent_->globalRotation().z_);
        float cos_angle = std::cos(parent_rotate);
        float sin_angle = std::sin(parent_rotate);

        t3::Vec2 rotate_pos(
            (position_.x_ * cos_angle) - (position_.y_ * sin_angle),
            (position_.x_ * sin_angle) + (position_.y_ * cos_angle)
        );

        rotate_pos += parent_->globalPosition();
        return rotate_pos;
    }
    
    
    ///
    /// 階層構造を加味した回転情報を取得
    Vec3 globalRotation() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return rotation_;
        }
        
        //  親がいる
        return rotation_ + parent_->globalRotation();
    }

    ///
    /// 階層構造を加味したスケールを取得
    t3::Vec2 globalScale() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return scale_;
        }
        
        
        return scale_ * parent_->globalScale();
    }



    ///
    /// 生成
    static Transform2DPtr create() {
        Transform2DPtr tr(T3_SYS_NEW Transform2D);
        return tr;
    }

private:
    ///
    /// 座標
    Vec2 position_;
    
    ///
    /// 回転
    Vec3 rotation_;
    
    ///
    /// スケール
    Vec2 scale_;
    
    ///
    /// 親の姿勢
    Transform2DPtr parent_;
};



TRI_CORE_NS_END


#endif  // TRI_TRANSFORM_HPP_INCLUDED



