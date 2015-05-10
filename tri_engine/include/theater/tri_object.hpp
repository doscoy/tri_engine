

#ifndef TRI_OBJECT_HPP_INCLUDED
#define TRI_OBJECT_HPP_INCLUDED

//  include
#include "../math/tri_math.hpp"

namespace t3 {

///
/// オブジェクト
class Object {
public:
    ///
    /// コンストラクタ
    Object();
    
    ///
    /// デストラクタ
    virtual ~Object();


public:
    ///
    /// 座標設定
    void position(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        position_.x_ = x;
        position_.y_ = y;
        position_.z_ = z;
    }
    
    ///
    /// 座標設定
    void position(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ = v;
    }
    
    ///
    /// 座標取得
    const Vec3& position() const {
        return position_;
    }
    
    ///
    /// 座標値加算
    void addPosition(
        const Vec3& v
    ) {
        calc_request_ = true;
        position_ += v;
    }
    
    ///
    /// 座標値加算
    void addPositionX(
        const float v
    ) {
        calc_request_ = true;
        position_.x_ += v;
    }
    
    ///
    /// 座標値加算
    void addPositionY(
        const float v
    ) {
        calc_request_ = true;
        position_.y_ += v;
    }
    
    ///
    /// 座標値加算
    void addPositionZ(
        const float v
    ) {
        calc_request_ = true;
        position_.z_ += v;
    }
    
    ///
    /// 回転設定
    void rotation(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        rotation_.x_ = x;
        rotation_.y_ = y;
        rotation_.z_ = z;
    }
    
    
    ///
    /// X回転設定
    void setRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ = r;
    }
    
    ///
    /// Y回転設定
    void setRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ = r;
    }
    
    ///
    /// Z回転設定
    void setRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ = r;
    }
    
    ///
    /// 回転設定
    void rotation(
        const Vec3& v
    ) {
        calc_request_ = true;
        rotation_ = v;
    }
    
    ///
    /// 回転取得
    const Vec3& rotation() const {
        return rotation_;
    }
    
    ///
    /// Z回転加算
    void addRotationX(
        const float r
    ) {
        calc_request_ = true;
        rotation_.x_ += r;
    }
    
    ///
    /// Y回転加算
    void addRotationY(
        const float r
    ) {
        calc_request_ = true;
        rotation_.y_ += r;
    }
    
    ///
    /// Z回転加算
    void addRotationZ(
        const float r
    ) {
        calc_request_ = true;
        rotation_.z_ += r;
    }
    
    ///
    /// スケール値設定
    void scale(
        float x,
        float y,
        float z
    ) {
        calc_request_ = true;
        scale_.x_ = x;
        scale_.y_ = y;
        scale_.z_ = z;
    }
    
    ///
    /// スケール値設定
    void scale(
        const Vec3& v
    ) {
        calc_request_ = true;
        scale_ = v;
    }
    
    ///
    /// スケール取得
    const Vec3& scale() const {
        return scale_;
    }
    
    ///
    /// 表示設定
    void setVisible(
        const bool visible
    ) {
        visible_ = visible;
    }

    ///
    /// 表示判定
    bool isVisible() const {
        return visible_;
    }

    ///
    /// SRT行列を取得
    const Mtx44* getTransformMatrix();

private:
    ///
    /// SRT行列生成
    void makeTransformMatrix();


private:
    ///
    /// 座標
    Vec3 position_;
    
    ///
    /// 回転
    Vec3 rotation_;
    
    ///
    /// スケール
    Vec3 scale_;
    
    ///
    /// 表示フラグ
    bool visible_;
    
    ///
    /// SRT行列
    Mtx44 transform_;
    
    ///
    /// 行列再計算リクエスト
    bool calc_request_;
};


}   // namespace t3



#endif  // TRI_OBJECT_HPP_INCLUDED
