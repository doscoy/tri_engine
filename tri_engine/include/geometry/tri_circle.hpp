
#ifndef TRI_CIRCLE_HPP_INCLUDED
#define TRI_CIRCLE_HPP_INCLUDED

//  include
#include "math/tri_vec2.hpp"

namespace t3 {


///
/// �~
class Circle {
public:
    ///
    /// �R���X�g���N�^
    Circle()
        : Circle(Vec2(0.0f, 0.0f), 1.0f)
    {}

    ///
    /// �R���X�g���N�^.
    /// ���W�A���a�w��
    Circle(
        const Vec2& pos,
        float radius
    )   : position_(pos)
        , radius_(radius)
    {}


public:
    ///
    /// �ʒu�ݒ�
    void position(
        const Vec2& pos ///< �ʒu
    ) {
        position_ = pos;
    }

    ///
    /// �ʒu�擾
    const Vec2& position() const {
        return position_;
    }
    
    ///
    /// ���a�ݒ�
    void radius(
        const float radius  ///< ���a
    ) {
        radius_ = radius;
    }
    
    ///
    /// ���a�擾
    float radius() const {
        return radius_;
    }


private:
    Vec2 position_; ///< �ʒu
    float radius_;  ///< ���a
};


}   // namespace t3


#endif  // TRI_CIRCLE_HPP_INCLUDED
