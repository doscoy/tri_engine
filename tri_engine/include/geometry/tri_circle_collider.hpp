#ifndef TRI_CIRCLE_COLLIDER_HPP_INCLUDED
#define TRI_CIRCLE_COLLIDER_HPP_INCLUDED

// include
#include "tri_collider.hpp"
#include "tri_circle.hpp"


namespace t3 {


///
/// �����蔻��I�u�W�F�N�g.
/// �~
class CircleCollider
    : public Collider {

public:
    ///
    /// �R���X�g���N�^
    CircleCollider(
        const HashString& name
    );
    ///
    /// �f�X�g���N�^
    ~CircleCollider() = default;
    
public:
    ///
    /// �����蔻��.
    /// �Ή~
    bool isHit(const CircleCollider& col) const override;

    ///
    /// �����蔻��.
    /// �Γ_
    bool isHit(const PointCollider& col) const override;

    ///
    /// �����蔻���ʎ擾
    const HashString& getCollisionType() const override;
    
public:
    static const HashString TYPE;

public:
    ///
    /// �ʒu�ݒ�
    void position(
        const Vec2& pos ///< �ʒu
    ) {
        circle_.position(pos);
    }

    ///
    /// ���a�ݒ�    
    void radius(
        const float radius  ///< ���a
    ) {
        circle_.radius(radius);
    }

    ///
    /// �~�擾
    const Circle& circle() const {
        return circle_;
    }

    void circle(const Circle& c) {
        circle_ = c;
    }

private:
    Circle circle_; ///< ����p�~

};


using CircleColliderPtr = std::shared_ptr<CircleCollider>;


}   // namespace t3

#endif  // TRI_CIRCLE_COLLIDER_HPP_INCLUDED

