#ifndef TRI_BOX_HPP_INCLUDED
#define TRI_BOX_HPP_INCLUDED


//  include
#include "util/tri_uncopyable.hpp"
#include "tri_object.hpp"


namespace t3 {

///
/// �{�b�N�X�I�u�W�F�N�g.
class Box
    : public Object
{
public:
    ///
    /// �R���X�g���N�^.
    Box()
        : size_(1,1,1)
    {}
    
    ///
    /// �f�X�g���N�^.
    virtual ~Box()
    {}

public:
    ///
    /// �T�C�Y�ݒ�
    void size(
        const Vec3& v
    ) {
        size_ = v;
    }

    ///
    /// �T�C�Y�ݒ�
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
    /// �T�C�Y�擾
    const Vec3& size() const {
        return size_;
    }

    ///
    /// �`��
    void render();

private:
    Vec3 size_;     ///< �T�C�Y
};


}   // namespace t3

#endif  // TRI_BOX_HPP_INCLUDED
