/**
    @file tri_box.hpp
    ゲームシーン用箱エンティティ.
*/

#ifndef TRI_BOX_HPP_INCLUDED
#define TRI_BOX_HPP_INCLUDED


//  include
#include "util/tri_uncopyable.hpp"
#include "tri_object.hpp"


namespace t3 {

///
/// ボックスオブジェクト.
class Box
    : public Object
{
public:
    ///
    /// コンストラクタ.
    Box()
        : size_(1,1,1)
    {}
    
    ///
    /// デストラクタ.
    virtual ~Box()
    {}

public:
    ///
    /// サイズ設定
    void size(
        const Vec3& v
    ) {
        size_ = v;
    }

    ///
    /// サイズ設定
    void size(
        const float x,
        const float y,
        const float z
    ) {
        size_.x_ = x;
        size_.y_ = y;
        size_.z_ = z;
    }

    ///
    /// サイズ取得
    const Vec3& size() const {
        return size_;
    }

    ///
    /// 描画
    void render();

private:
    Vec3 size_;     ///< サイズ
};


}   // namespace t3

#endif  // TRI_BOX_HPP_INCLUDED
