
#ifndef TRI_COLLIDER_HPP_INCLUDED
#define TRI_COLLIDER_HPP_INCLUDED

//  include
#include "util/tri_hash_string.hpp"
#include "util/tri_unique_id.hpp"
#include "util/tri_any.hpp"
#include "base/tri_std.hpp"


namespace t3 {

//  �O���錾
class PointCollider;
class CircleCollider;

///
/// �����蔻��I�u�W�F�N�g
class Collider {

public:
    ///
    /// �R���X�g���N�^
    Collider(
        const HashString& name
    );

    ///
    /// �f�X�g���N�^
    virtual ~Collider(){};
    
public:
    ///
    /// �����蔻��
    virtual bool isHit(
        const PointCollider& col    ///< �_
    ) const {
        return false;
    }
    
    ///
    /// �����蔻��
    virtual bool isHit(
        const CircleCollider& col   ///< �~
    ) const {
        return false;
    }

    ///
    /// �����蔻��^�C�v�擾
    virtual const HashString& getCollisionType() const = 0;

public:
    ///
    /// �R���C�_ID�擾
    const UniqueID& colliderID() const {
        return collider_id_;
    }
    
    ///
    /// �R���C�_���擾
    const HashString& colliderName() const {
        return collider_name_;
    }

    ///
    /// �I�[�i�[�ݒ�
    void owner(Any any) {
        owner_ = any;
    }
    
    ///
    /// �I�[�i�[�擾
    Any& owner() {
        return owner_;
    }
    
    ///
    /// �I�[�i�[�擾
    const Any& owner() const {
        return owner_;
    }


public:
    ///
    /// �R���C�_���m�̔���
    bool operator ==(const Collider& rhs) {
        return colliderID() == rhs.colliderID();
    }

private:
    UniqueID collider_id_;      ///< �R���C�_ID
    HashString collider_name_;  ///< �R���C�_��
    Any owner_;                 ///< �I�[�i�[
};

///
/// �R���C�_�̃|�C���^
using ColliderPtr = SharedPtr<Collider>;

        

}   // namespace t3


#endif
