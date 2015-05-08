
#ifndef TRI_FADE_LAYER_HPP_INCLUDED
#define TRI_FADE_LAYER_HPP_INCLUDED

//  include
#include "tri_draw_layer.hpp"
#include "tri_color.hpp"


namespace t3 {

///
/// �t�F�[�h���C���[
class FadeLayer
    : public DrawLayer
{
public:
    ///
    /// �R���X�g���N�^
    FadeLayer();

    ///
    /// �R���X�g���N�^
    FadeLayer(const String& name, const int priority);

    ///
    /// �f�X�g���N�^
    ~FadeLayer();


public:
    ///
    /// �t�F�[�h�X�s�[�h�ݒ�
    void setFadeSpeed(
        const float speed
    ) {
        fade_speed_ = speed;
    }
    
    ///
    /// �t�F�[�h�C��
    void fadeIn(
        const t3::tick_t sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = true;
        fade_speed_ = t3::frameSec<60>() / sec * -1;
    }
    
    ///
    /// �t�F�[�h�A�E�g
    void fadeOut(
        const tick_t sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = false;
        fade_speed_ = t3::frameSec<60>() / sec;
    }
    
    
    ///
    /// �t�F�[�h����
    bool isFadeEnd() const {
        return fading_ == false;
    }
    
    ///
    /// �t�F�[�h�C���I������
    bool isFadeInEnd() const {
        if (fade_in_) {
            if (fading_ == false) {
                return true;
            }
        }
        
        return false;
    }
    
    ///
    /// �t�F�[�h�A�E�g�I������
    bool isFadeOutEnd() const {
        if (!fade_in_) {
            if (fading_ == false) {
                return true;
            }
        }
        return false;
    }
    

    ///
    /// �t�F�[�h�J���[�̐ݒ�
    void setFadeColor(
        int r,
        int g,
        int b
    ) {
        fade_color_.red(r);
        fade_color_.green(g);
        fade_color_.blue(b);
    }
    
    ///
    /// �t�F�[�h�J���[�̐ݒ�
    void setFadeColor(
        const Color& c
    ) {
        fade_color_ = c;
    }
    
    ///
    /// �t�F�[�h�p�����[�^�̐ݒ�
    void setupFadeParam(
        float fade_alpha,
        const Color& c
    ) {
        fading_ = false;
        alpha_ = fade_alpha;
        fade_color_ = c;
    }


private:
    ///
    /// �t�F�[�h�̍X�V�R�[���o�b�N
    void fadeUpdate(DrawLayer* const, tick_t);

    ///
    /// �t�F�[�h�̕`��R�[���o�b�N
    void fadeRender(DrawLayer* const);



private:
    bool fading_;           ///< �t�F�[�h�����ǂ����̃t���O
    bool fade_in_;          ///< �t�F�[�h�C�����ǂ����̃t���O
    float fade_speed_;      ///< �t�F�[�h���x
    Color fade_color_;      ///< �t�F�[�h�J���[
    float alpha_;           ///< �����x
};


}   // namesapce t3




#endif  // TRI_FADE_LAYER_HPP_INCLUDED
