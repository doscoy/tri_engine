
#ifndef TRI_RECTANGLE_HPP_INCLUDED
#define TRI_RECTANGLE_HPP_INCLUDED

//  include
#include "../math/tri_vec2.hpp"

namespace t3 {

///
/// 矩形プリミティブ
class Rectangle {
public:
    
    ///
    /// コンストラクタ
    Rectangle()
        : min_(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max())
        , max_(
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min())
        , size_()
        , center_()
    {
        calcCenterFromMinMax();
    }
    
    ///
    /// コンストラクタ
    Rectangle(
        const Vec2& min,
        const Vec2& max
    )   : min_(min)
        , max_(max)
        , size_()
        , center_()
    {
        calcCenterFromMinMax();
    }
    
    
    
    ///
    /// デストラクタ
    ~Rectangle()
    {
    }
    
public:
    ///
    /// 数値をリセット
    void reset() {
        min_ = Vec2(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max());
        max_ = Vec2(
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min());
        
        calcCenterFromMinMax();
    }
    
    ///
    /// 中心とサイズから矩形を構築
    void setupFromCenterSize(
        const Vec2& center,
        const Vec2& size
    ) {
        //  下限上限を計算
        Vec2 half_size = size / 2;
        min_ = center - half_size;
        max_ = center + half_size;
        
        //  中心
        center_ = center;
        
        //  サイズ
        size_ = size;
    }
    
    ///
    /// 点から矩形を構築
    void setupFromPoint(const Vec2& p) {
        if (min_.x_ > p.x_) {
            min_.x_ = p.x_;
        }
        if (min_.y_ > p.y_) {
            min_.y_ = p.y_;
        }
        if (max_.x_ < p.x_) {
            max_.x_ = p.x_;
        }
        if (max_.y_ < p.y_) {
            max_.y_ = p.y_;
        }
    }

public:
    ///
    /// 最小値設定
    void min(const Vec2& min) {
        min_ = min;
        calcCenterFromMinMax();
    }

    ///
    /// 最小値を取得
    const Vec2& min() const {
        return min_;
    }
    
    ///
    /// 最大値を設定
    void max(const Vec2& max) {
        max_ = max;
        calcCenterFromMinMax();
    }
    
    ///
    /// 最大値を取得
    const Vec2& max() const {
        return max_;
    }

    ///
    /// 中心点を取得
    const Vec2& center() const {
        return center_;
    }
    
    ///
    /// 中心点を設定
    const Vec2& size() const {
        return size_;
    }
    
    ///
    /// サイズを設定
    void size(const Vec2& s) {
        size_ = s;
        calcMinMaxFromSize();
    }

    
private:
    ///
    /// 最小値最大値から中心とサイズを計算
    void calcCenterFromMinMax() {
        size_ = max_ - min_;
        center_ = min_ + (size_ / 2);
    }
    ///
    /// 中心とサイズから最小値最大値を計算
    void calcMinMaxFromSize() {
        Vec2 half = size_ / 2;
        min_ = center_ - half;
        max_ = center_ + half;
    }
    
private:

    ///
    /// 最小値
    Vec2 min_;
    
    ///
    /// 最大値
    Vec2 max_;

    ///
    /// サイズ
    Vec2 size_;
    
    ///
    /// 中心点
    Vec2 center_;

};

}   // namespace t3

#endif  // TRI_RECTANGLE_HPP_INCLUDED
