
#ifndef TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED
#define TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

//  include
#include "../gfx/tri_render_layer.hpp"
#include "tri_debug_string_buffer.hpp"
#include "../gfx/tri_color.hpp"

namespace t3 {

///
/// �f�o�b�O�����\�����C��
class DebugStringLayer
    : public RenderLayer
{
public:
    ///
    /// �R���X�g���N�^
    DebugStringLayer(const char* const name = "DEBUG SCREEN");

    ///
    /// �f�X�g���N�^
    virtual ~DebugStringLayer();

public:
    ///
    /// �����ǉ�
    void writeString(
        const float x,
        const float y,
        const uint32_t color,
        const int size,
        const char* const str
    );

protected:
    ///
    /// �X�V�֐�
    void updateLayer(tick_t delta_time) override;

    ///
    /// �`��֐�
    void drawLayer() override;


protected:
    DebugStringBuffer debug_string_buffer_; ///<  ������ۑ��p�o�b�t�@

};



} // namespace t3


#endif // TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

