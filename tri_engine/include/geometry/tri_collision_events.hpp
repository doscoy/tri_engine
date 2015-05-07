
#ifndef TRI_COLLISION_EVENTS_HPP_INCLUDED
#define TRI_COLLISION_EVENTS_HPP_INCLUDED

//  include
#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "util/tri_unique_id.hpp"
#include "tri_collider.hpp"

namespace t3 {

///
/// �R���C�_���m�̃y�A
using CollisionPair = std::pair<ColliderPtr, ColliderPtr>;
    
///
/// �R���W�����C�x���g
class CollisionEvent
    : public EventBase {
public:
    ///
    /// �C�x���g�^�C�v
    static const EventType TYPE;

    ///
    /// �C�x���g�^�C�v�擾
    const EventType& eventType() const override {
        return TYPE;
    }

    ///
    /// �Ώۂ̃y�A���w���ID���܂�ł��邩����
    bool hasID(const UniqueID& id) const {
        if (id == collision_pair_.first->colliderID()) {
            return true;
        } else if (id == collision_pair_.second->colliderID()) {
            return true;
        }
        
        return false;
    }

    ///
    /// �w��ID����Ȃ����̃I�[�i�[�I�u�W�F�N�g���擾
    template <typename T>
    T getOtherOwner(const UniqueID& id) const {
        Any* owner = nullptr;
        if (collision_pair_.first->colliderID() == id) {
            owner = &collision_pair_.second->owner();
        } else {
            owner = &collision_pair_.first->owner();
        }
        return any_cast<T>(*owner);
    }



    Vec2 pos_;  ///< �ʒu
    CollisionPair collision_pair_;  ///< �y�A
};


}   // namespace t3

#endif  // TRI_COLLISION_EVENTS_HPP_INCLUDED
