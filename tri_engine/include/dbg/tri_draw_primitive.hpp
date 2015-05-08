#ifndef TRI_DRAW_PRIMITIVE_HPP_INCLUDED
#define TRI_DRAW_PRIMITIVE_HPP_INCLUDED

//  include
#include "../math/tri_math_types.hpp"
#include "../gfx/tri_color.hpp"


namespace t3 {


//  �O���錾
class Plane;
class Segment;



///
/// �v���~�e�B�u�`��̏�����
void initializeDrawPrimitive();

///
/// �_��`��
void drawPoint(
    const Vec3& pos,    ///< ���W
    const Color& color  ///< �F
);


///
/// ������`��
void drawSegment(
    const Segment& segment, ///< ����
    const Color& color,     ///< �F
    const float width       ///< ��
);

///
/// 3����`��
void drawAxis(
    const Vec3& pos     ///< ���W
);

///
/// 2D��`��`��.
/// �ŏ��l�ƕ����w��
void drawRectangleMinSize(
     const Vec2& min,   ///< �ŏ��l
     const Vec2& size,  ///< ��
     const Color& color ///< �F
);

///
/// 2D��`��`��.
/// ���S�_�ƕ����w��
void drawRectangleCenterSize(
     const Vec2& center,    ///< ���S�_
     const Vec2& size,      ///< �T�C�Y
     const Color& color     ///< �F
);

///
/// 2D��`��`��.
/// ����ƉE�����w��
void drawRectangleViewport(
    const Vec2& left_top,       ///< ����
    const Vec2& right_bottom,   ///< �E��
    const Color& color          ///< �F
);


///
/// ���ʂ�`��
void drawPlane(
    const Vec3& center, ///< ���ʂ̒��S
    const Vec3& normal, ///< ���ʂ̖@��
    const Vec3& size,   ///< ���ʂ̃T�C�Y
    const Color& color  ///< �F
);




}   // namespace t3



#endif // TRI_DRAW_PRIMITIVE_HPP_INCLUDED