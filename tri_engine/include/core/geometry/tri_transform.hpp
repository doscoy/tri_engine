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
	Position2D& position() {
        return position_;
    }
    
    ///
    /// 座標を取得
    const Position2D& position() const {
        return position_;
    }
    
    ///
    /// 座標を設定
    void position(
        const Position2D& pos
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
	Rotation& rotation() {
        return rotation_;
    }
    
    ///
    /// 回転情報を取得
    const Rotation& rotation() const {
        return rotation_;
    }
    
    ///
    /// 回転情報を設定
    void rotation(
        const Rotation& rot
    ) {
        rotation_ = rot;
    }
    
    ///
    /// 回転情報を設定
    void rotation(
        const Degree x,
        const Degree y,
        const Degree z
    ) {
        rotation_.x_ = x;
        rotation_.y_ = y;
        rotation_.z_ = z;
    }
    
    ///
    /// 角度を移動
    void rotateX(
        const Degree r
    ) {
        rotation_.x_ += r;
    }
    
    ///
    /// 角度を移動
    void rotateY(
        const Degree r
    ) {
        rotation_.y_ += r;
    }
    
    ///
    /// 角度を移動
    void rotateZ(
        const Degree r
    ) {
        rotation_.z_ += r;
    }
    
    ///
    ///  スケールを取得
    Scale2D& scale() {
        return scale_;
    }
    
    ///
    /// スケールを取得
    const Scale2D& scale() const {
        return scale_;
    }
    
    ///
    /// スケールを設定
    void scale(
        const Scale2D& scale
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
    t3::Position2D globalPosition() const {
        if (!hasParent()) {
            //  親が居ないのでただ座標を返す
            return position_;
        }
        
        //  親が居る
        //  親の情報と掛けあわせてグローバル座標を計算
        
        
        //  親の回転の影響を受けた座標
        Radian parent_rotate = toRadian(parent_->globalRotation().z_);
        float cos_angle = std::cos(parent_rotate.value());
        float sin_angle = std::sin(parent_rotate.value());

        t3::Position2D rotate_pos(
            (position_.x_ * cos_angle) - (position_.y_ * sin_angle),
            (position_.x_ * sin_angle) + (position_.y_ * cos_angle)
        );

        rotate_pos += parent_->globalPosition();
        return rotate_pos;
    }
    
    
    ///
    /// 階層構造を加味した回転情報を取得
    Rotation globalRotation() const {
        if (!hasParent()) {
            //  親が居ないのでただ回転情報を返す
            return rotation_;
        }
        
        //  親がいる
        return rotation_ + parent_->globalRotation();
    }

    ///
    /// 階層構造を加味したスケールを取得
    Scale2D globalScale() const {
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
    Position2D position_;
    
    ///
    /// 回転
    Rotation rotation_;
    
    ///
    /// スケール
    Scale2D scale_;
    
    ///
    /// 親の姿勢
    Transform2DPtr parent_;
};



TRI_CORE_NS_END


#endif  // TRI_TRANSFORM_HPP_INCLUDED



