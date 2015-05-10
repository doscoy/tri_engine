

#ifndef TRI_OBJECT_HPP_INCLUDED
#define TRI_OBJECT_HPP_INCLUDED

//  include
#include "math/tri_math.hpp"


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
    ~Object();

public:
    ///
    /// トランスフォーム行列を取得
    const Mtx44* getTransformMatrix();
    
private:
    ///
    /// トランスフォーム行列を計算
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
    /// 描画判定
    bool visible_;
    
    ///
    /// 行列
    Mtx44 transform_;
    
    ///
    /// 行列の再計算リクエスト
    bool calc_request_;
};


}   // namespace t3


#endif
