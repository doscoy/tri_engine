#ifndef TRI_FRUSTUM_HPP_INCLUDED
#define TRI_FRUSTUM_HPP_INCLUDED


//  include
#include "../math/tri_vec3.hpp"
#include "tri_plane.hpp"

namespace t3 {


///
/// �t���X�^��
class Frustum {
public:
    ///
    /// �R���X�g���N�^
    Frustum();

    ///
    /// �f�X�g���N�^
    ~Frustum();

public:
    ///
    /// �ʃ^�C�v
    enum Side {
        SIDE_NEAR,      ///< ��O
        SIDE_FAR,       ///< ��
        SIDE_TOP,       ///< ��
        SIDE_RIGHT,     ///< �E
        SIDE_BOTTOM,    ///< ��
        SIDE_LEFT,      ///< ��
        
        SIDE_NUM        ///< �ʑ���
    };


public:
    ///
    /// ����p��ݒ�
    void setFov(float fov){
        fov_ = fov;
    }

    ///
    /// �A�X�y�N�g���ݒ�
    void setAspect(float aspect){
        aspect_ = aspect;
    }

    ///
    /// �j�A�N���b�v�ʂ�ݒ�
    void setNear(float near){
        near_ = near;
    }

    ///
    /// �t�@�[�N���b�v�ʂ�ݒ�
    void setFar(float far){
        far_ = far;
    }

    ///
    /// �t���X�^��������
    void initializeFrustum(
        float fov,          ///< ����p
        float aspect,       ///< �A�X�y�N�g��
        float near,         ///< �j�A�N���b�v
        float far,          ///< �t�@�[�N���b�v
        const Vec3& front,  ///< �O�x�N�g��
        const Vec3& right,  ///< �E�x�N�g��
        const Vec3& up,     ///< ��x�N�g��
        const Vec3& pos     ///< �ʒu
    );

    ///
    /// �ʂ��\�����镽�ʎ擾
    const Plane* getPlane(
        int side    ///< �ʃ^�C�v
    ) const {
        return &plane_[side];
    }

    ///
    /// ��������
    bool isInside(
        const Vec3& point   ///< �ʒu
    );

    ///
    /// ��������.
    /// �ʒu�Ɣ��a
    bool isInSide(
		const Vec3& point,  ///< �ʒu
		float radius        ///< ���a
    );

private:
    Plane plane_[SIDE_NUM];     ///< �t���X�^�����\������e��
    Vec3 near_clip_[4];         ///< ��O�̖ʍ��W
    Vec3 far_clip_[4];          ///< ���̖ʍ��W
    Vec3 pos_;                  ///< �ʒu
    float fov_;                 ///< ����p
    float aspect_;              ///< �A�X�y�N�g��
    float near_;                ///< �O�ʃI�t�Z�b�g
    float far_;                 ///< ���ʃI�t�Z�b�g
 
};


}   // namespace t3


#endif  // TRI_FRUSTUM_HPP_INCLUDED
