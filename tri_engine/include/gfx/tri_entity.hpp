#ifndef TRI_ENTITY_HPP_INCLUDED
#define TRI_ENTITY_HPP_INCLUDED

//  include
#include "math/tri_matrix.hpp"


namespace t3 {


///
/// �G���e�B�e�B.
/// �V�[���O���t�ɓo�^����邠������̂̊��
class Entity {
protected:
    ///
    /// �R���X�g���N�^
    Entity(){};

    ///
    /// �f�X�g���N�^
    virtual ~Entity(){};
    
public:
    ///
    /// �`�悷����̂�����
    virtual bool isRenderable() const {
        return false;
    }
    
    ///
    /// �`��
    virtual void render(const Mtx44&){}
};


}   // namespace t3


#endif // TRI_ENTITY_HPP_INCLUDED