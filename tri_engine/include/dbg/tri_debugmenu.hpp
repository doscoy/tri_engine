/**
    @file tri_debugmenu.hpp
    �f�o�b�O���j���[.
*/

#ifndef TRI_DEBUGMENU_HPP_INCLUDED
#define TRI_DEBUGMENU_HPP_INCLUDED

//  include
#include "tri_debugmenu_frame.hpp"
#include "tri_debugmenu_items.hpp"
#include "tri_virtual_pad.hpp"

namespace t3 {

///
/// �f�o�b�O���j���[
class DebugMenu
    : public Singleton<DebugMenu>
{
public:
    ///
    /// �R���X�g���N�^
    DebugMenu();

    ///
    /// �f�X�g���N�^
    ~DebugMenu();
    
public:
    ///
    /// ���j���[���J��
    void openMenu();

    ///
    /// ���j���[�����
    void closeMenu();
    
    ///
    /// �L���ݒ�
    void enable( const bool enable ){
        enable_ = enable;
    }
    
    ///
    /// �L������
    bool isEnable() const {
        return enable_;
    }
    
    ///
    /// �I�[�v������
    bool isOpened() const {
        return open_;
    }

    ///
    /// ���[�g���j���[�擾
    DebugMenuFrame& rootMenu() {
        return menu_root_;
    }
    
    ///
    /// ���[�g���j���[�擾
    const DebugMenuFrame& rootMenu() const {
        return menu_root_;
    }
       
    ///
    /// �X�V
    void update( tick_t delta_time );
    
    ///
    /// �`��
    void render();
    
    ///
    /// �t���[���ɒǉ�
    void attachFrame(
        DebugMenuFrame& frame
    ){
        frame.attachSelf( menu_root_ );
    }
    
    ///
    /// �o�[�`�����p�b�h�擾
    const VirtualPad& virtualPad() const {
        return vpad_;
    }
            
private:
    VirtualPad vpad_;               ///< �o�[�`�����p�b�h
    DebugMenuFrame menu_root_;      ///< �f�o�����[�g
    bool enable_;                   ///< �L������
    bool open_;                     ///< �I�[�v������
    
    short left_offset_;             ///< ���[����̃I�t�Z�b�g�ʒu
    
};





}   // namespace t3

#endif // TRI_DEBUGMENU_HPP_INCLUDED