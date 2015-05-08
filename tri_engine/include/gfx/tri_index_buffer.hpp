
#ifndef TRI_INDEX_BUFFER_HPP_INCLUDED
#define TRI_INDEX_BUFFER_HPP_INCLUDED

//  include
#include "cross_sdk.hpp"

namespace t3 {

///
/// �C���f�b�N�X�o�b�t�@
class IndexBuffer {
public:
    ///
    /// �R���X�g���N�^
    IndexBuffer()
        : buffer_id_()
    {
        cross::RenderSystem::createBuffer(&buffer_id_);
    }
    
    ///
    /// �f�X�g���N�^
    ~IndexBuffer() {
        cross::RenderSystem::deleteBuffer(&buffer_id_);
    }
    
public:
    ///
    /// ���̃C���f�b�N�X�o�b�t�@�������_�����O�V�X�e���ɕR�t��
    void bind() const {
        cross::RenderSystem::bindBuffer(cross::RenderSystem::BufferType::TYPE_INDEX, buffer_id_);
    }

private:
    cross::RenderSystem::BufferID buffer_id_;   ///< �o�b�t�@ID
};


}   // namespace t3


#endif  // TRI_VERTEX_BUFFER_HPP_INCLUDED
