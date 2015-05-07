
#ifndef TRI_AABB_HPP_INCLUDED
#define TRI_AABB_HPP_INCLUDED


#include "../math/tri_vec3.hpp"

namespace t3 {

///
/// �o�E���f�B���O�{�b�N�X
///
class AABB {
public:
    ///
    /// �R���X�g���N�^.
    /// �f�t�H���g��min_,mix_��float�̌��E�l�ŏ����������
    AABB()
        : min_(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max())
        , max_(
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min())
    {}
    
    ///
    /// �R���X�g���N�^.
    /// �ŏ��l�A�ő�l�w��
    AABB(
        const Vec3& min,    ///< �ŏ��l
        const Vec3& max     ///< �ő�l
    )   : min_(min)
        , max_(max)
    {}
    
    
    //  �f�X�g���N�^
    ~AABB()
    {}
    
public:
    ///
    /// AABB�̊g��.
    /// �󂯎�������W���܂ޑ傫���Ɋg������
    void margePoint(
        const Vec3& p   ///< ���W
    ) {
        //  x��
        if (min_.x_ > p.x_) {
            min_.x_ = p.x_;
        } else if (max_.x_ < p.x_) {
            max_.x_ = p.x_;
        }
        
        //  y��
        if (min_.y_ > p.y_) {
            min_.y_ = p.y_;
        } else if (max_.y_ < p.y_) {
            max_.y_ = p.y_;
        }
        
        //  z��
        if (min_.z_ > p.z_) {
            min_.z_ = p.z_;
        } else if (max_.z_ < p.z_) {
            max_.z_ = p.z_;
        }
    }
    
    ///
    /// �ŏ��l�ݒ�.
    void min(
        const Vec3& min ///< �ŏ��l
    ) {
        min_ = min;
    }

    ///
    /// �ŏ��l�擾.
    const Vec3& min() const {
        return min_;
    }
    
    /// 
    /// �ő�l�ݒ�.
    void max(
        const Vec3& max ///< �ő�l
    ) {
        max_ = max;
    }
    
    ///
    /// �ő�l�擾.
    const Vec3& max() const {
        return max_;
    }
    
    ///
    /// �_��AABB�̓���������
    bool isInside(
        const Vec3& p   ///< ���肷��_
    ) const {
        //  x
        if (p.x_ > max_.x_) {
            return false;
        }
        if (p.x_ < min_.x_) {
            return false;
        }
        
        //  y
        if (p.y_ > max_.y_) {
            return false;
        }
        if (p.y_ < min_.y_) {
            return false;
        }
        
        //  z
        if (p.z_ > max_.z_) {
            return false;
        }
        if (p.z_ < min_.z_) {
            return false;
        }
        
        return true;
    }

    /// ���S�_�擾.
    Vec3 center() const {
        return (min_ + max_) * 0.5f;
    }
    
    ///
    /// ���a�擾.
    Vec3 radius() const {
        return (max_ - min_) * 0.5f;
    }


private:
    Vec3 min_;          ///< �ŏ��l
    Vec3 max_;          ///< �ő�l

};




}   // namespace t3

#endif  // TRI_AABB_HPP_INCLUDED
