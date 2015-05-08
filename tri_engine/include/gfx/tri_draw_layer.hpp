
#ifndef TRI_DRAW_LAYER_HPP_INCLUDED
#define TRI_DRAW_LAYER_HPP_INCLUDED

//  include
#include <iostream>
#include <functional>
#include "tri_render_layer.hpp"
#include "../util/tri_method_callback.hpp"


namespace t3 {


///
/// �`�惌�C���[
class DrawLayer
    : public RenderLayer
{
    using self_t = DrawLayer;
protected:
    using UpdateCallback = MethodCallback2<self_t, self_t* const, tick_t>;  ///< �X�V�R�[���o�b�N�^
    using RenderCallback = MethodCallback1<self_t, self_t* const>;          ///< �`��R�[���o�b�N�^

public:
    ///
    /// �R���X�g���N�^
    DrawLayer();

    ///
    /// �R���X�g���N�^
    explicit DrawLayer(const String name, const int priority);

    ///
    /// �f�X�g���N�^
    virtual ~DrawLayer();
    
    ///
    /// �X�V�R�[���o�b�N�ݒ�
    template <typename T>
    void setUpdateCallback(
        T* instance,
        void (T::*update_func)(self_t*, tick_t)
    ){
        MethodCallback2<T, self_t*, tick_t> callback(instance, update_func);
        update_func_ = (UpdateCallback&)callback;
    }
    
    ///
    /// �`��R�[���o�b�N�ݒ�
    template <typename T>
    void setRenderCallback(
        T* instance,
        void (T::*render_func)(self_t*)
    ){
        MethodCallback1<T, self_t*> callback(instance, render_func);
        render_func_ = (RenderCallback&)callback;
    }
    
protected:
    ///
    /// ���C���[�̍X�V
    void updateLayer(tick_t delta_time) override;

    ///
    /// ���C���[�̕`��
    void drawLayer() override;

    ///
    /// �������Ȃ��X�V�R�[���o�b�N
    void nullUpdate(self_t* const, tick_t) {}

    ///
    /// �������Ȃ��`��R�[���o�b�N
    void nullRender(self_t* const) {}
    
private:
    UpdateCallback update_func_;    ///< �A�b�v�f�[�g���R�[���o�b�N�֐�
    RenderCallback render_func_;    ///< �`�掞�R�[���o�b�N�֐�
};



}   // namespace t3




#endif // TRI_DRAW_LAYER_HPP_INCLUDED
