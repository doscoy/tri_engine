#ifndef TRI_CINEMA_LAYER_HPP_INCLUDED
#define TRI_CINEMA_LAYER_HPP_INCLUDED


//  include
#include "tri_render_layer.hpp"
#include "tri_shader.hpp"
#include "tri_texture.hpp"


namespace t3 {
  

///
/// �V�l�}���C���[.
/// �����_�����O�ς݃e�N�X�`����\�郌�C���[
class CinemaLayer
    : public RenderLayer {
    
public:
    ///
    /// �R���X�g���N�^
    CinemaLayer();

    ///
    /// �R���X�g���N�^.
    /// ���C�����ƗD��x��ݒ�
    CinemaLayer(
        const String& name, ///< ���C���[��
        const int priority  ///< �D��x
    );

    ///
    /// �f�X�g���N�^
    virtual ~CinemaLayer();


public:
    ///
    /// �g�p����e�N�X�`����ݒ�
    void texture(
        TexturePtr tex
    ) {
        texture_ = tex;
    }
    
    ///
    /// �f�t�H���g�̃V�F�[�_���g�p
    void useDefaultShader() {
        shader_ = default_shader_;
    }
    
    ///
    /// �V�F�[�_��ݒ�
    void shader(ShaderPtr shader) {
        shader_ = shader;
    }
private:
    ///
    /// �X�V�֐�
    void updateLayer(tick_t delta_time) override;

    ///
    /// �`��֐�
    void drawLayer() override;
    

private:
    ShaderPtr shader_;          ///< �V�F�[�_
    ShaderPtr default_shader_;  ///< �f�t�H���g�V�F�[�_
    TexturePtr texture_;        ///< �e�N�X�`��
};
  
  
}   // namespace t3



#endif  // TRI_CINEMA_LAYER_HPP_INCLUDED
