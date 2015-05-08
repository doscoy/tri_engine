

#ifndef TRI_GUI_SWAP_BUTTON_HPP_INCLUDED
#define TRI_GUI_SWAP_BUTTON_HPP_INCLUDED

//  include
#include "tri_gui_button.hpp"

namespace t3 {



///
/// �X���b�v�{�^��.
/// �{�^���������x��A,B���؂�ւ��
class SwapButton
    : Uncopyable {
public:
    ///
    /// �R���X�g���N�^
    SwapButton();

    ///
    /// �f�X�g���N�^
    ~SwapButton();
    
public:
    ///
    /// �X�v���C�g�o�^
    void setupSprite(
        SpritePtr a,
        SpritePtr b,
        bool default_a = true
    );
    
    
    ///
    /// �C�x���g
    void triggeredEvent(
        EventPtr event_a,
        EventPtr event_b
    );
    
    ///
    /// �{�^���̃X�v���C�g�̃T�C�Y�ݒ�
    void size(float s) {
        a_.size(s);
        b_.size(s);
    }
    
    ///
    /// �{�^���̃X�v���C�g�̃T�C�Y�ݒ�
    void size(const Vec2& s) {
        a_.size(s);
        b_.size(s);
    }
    
    ///
    /// ����G���A�ݒ�
    void hitAreaSize(const float s) {
        a_.hitAreaSize(s);
        b_.hitAreaSize(s);
    }

    ///
    /// ����G���A�ݒ�
    void hitAreaSize(const Vec2 s) {
        a_.hitAreaSize(s);
        b_.hitAreaSize(s);
    }
    
    ///
    /// ���W�ݒ�
    void position(const Vec2& pos) {
        a_.position(pos);
        b_.position(pos);
    }


private:
    ///
    /// �{�^��A�������ꂽ���ɌĂ΂��
    void onTriggeredA(const Event&);

    ///
    /// �{�^��B�������ꂽ���ɌĂ΂��
    void onTriggeredB(const Event&);

private:
    Button a_;  ///< �{�^��A
    Button b_;  ///< �{�^��B
    UniqueID swap_button_id_;   ///< �X���b�v�{�^����ID
    EventPtr a_event_;  ///< �{�^��A�̃C�x���g
    EventPtr b_event_;  ///< �{�^��B�̃C�x���g
};


}   // namespace t3



#endif  // TRI_GUI_SWAP_BUTTON_HPP_INCLUDED
