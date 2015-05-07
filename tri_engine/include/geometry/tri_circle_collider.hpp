#ifndef TRI_CIRCLE_COLLIDER_HPP_INCLUDED
#define TRI_CIRCLE_COLLIDER_HPP_INCLUDED

// include
#include "tri_collider.hpp"
#include "tri_circle.hpp"


namespace t3 {


///
/// 当たり判定オブジェクト.
/// 円
class CircleCollider
    : public Collider {

public:
    ///
    /// コンストラクタ
    CircleCollider(
        const HashString& name
    );
    ///
    /// デストラクタ
    ~CircleCollider() = default;
    
public:
    ///
    /// 当たり判定.
    /// 対円
    bool isHit(const CircleCollider& col) const override;

    ///
    /// 当たり判定.
    /// 対点
    bool isHit(const PointCollider& col) const override;

    ///
    /// 当たり判定種別取得
    const HashString& getCollisionType() const override;
    
public:
    static const HashString TYPE;

public:
    ///
    /// 位置設定
    void position(
        const Vec2& pos ///< 位置
    ) {
        circle_.position(pos);
    }

    ///
    /// 半径設定    
    void radius(
        const float radius  ///< 半径
    ) {
        circle_.radius(radius);
    }

    ///
    /// 円取得
    const Circle& circle() const {
        return circle_;
    }

    void circle(const Circle& c) {
        circle_ = c;
    }

private:
    Circle circle_; ///< 判定用円

};


using CircleColliderPtr = std::shared_ptr<CircleCollider>;


}   // namespace t3

#endif  // TRI_CIRCLE_COLLIDER_HPP_INCLUDED

