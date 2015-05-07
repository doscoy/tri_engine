#ifndef TRI_COLLISION_MANAGER_HPP_INCLUDED
#define TRI_COLLISION_MANAGER_HPP_INCLUDED

//  include
#include "util/tri_hash_string.hpp"
#include "geometry/tri_collision_events.hpp"
#include "base/tri_event.hpp"
#include "math/tri_vec2.hpp"
#include "util/tri_singleton.hpp"
#include "base/tri_std.hpp"


namespace t3 {

///
/// �R���C�_�W��
using Colliders = List<SharedPtr<Collider>>;

///
/// �R���C�_�W���̃|�C���^
using CollidersPtr = SharedPtr<Colliders>;


///
/// �R���W�����}�l�[�W��
class CollisionManager
    : public Singleton<CollisionManager>
{
    friend class Singleton<CollisionManager>;

private:
    ///
    /// ����ς݃y�A
    using JudgedPairs = Vector<CollisionPair>;
public:

    ///
    /// �R���C�_�ǉ�
    void addCollider(
        ColliderPtr collider,   ///< �R���C�_
        HashString target       ///< �Ώۂ̖��O
    );

    ///
    /// �R���C�_�폜
    void removeCollider(
        ColliderPtr collider    ///< �R���C�_
    );


    ///
    /// �������蔻��
    void collisionDetection();

private:
    ///
    /// �y�A�̓����蔻��
    void judgeColliderPairs(
        ColliderPtr& a,
        ColliderPtr& b
    );
    
    ///
    /// ����ς݃y�A��
    bool isJudgedPair(
        const CollisionPair& pair
    );
    
private:
    ///
    ///  �R���C�_�R���e�i
    using CollidersMap = std::map<HashString, CollidersPtr>;

    CollidersMap colliders_;            ///< �Ǘ��R���C�_
    CollidersMap same_target_group_;    ///< ���������蔻��Ώۂ����O���[�v
    JudgedPairs judged_pairs_;          ///< ����ς݂̃y�A
};



}   // namespace t3


#endif  // TRI_COLLISION_MANAGER_HPP_INCLUDED
