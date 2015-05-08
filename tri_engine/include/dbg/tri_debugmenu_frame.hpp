
#ifndef TRI_DEBUGMENU_FRAME_HPP_INCLUDED
#define TRI_DEBUGMENU_FRAME_HPP_INCLUDED

//  include
#include "tri_debugmenu_label.hpp"


namespace t3 {
    
///
/// �f�o�b�O���j���[���R���e�i
using DebugMenuList = List<DebugMenuLabel*>;


///
/// �f�o�b�O���j���[�Ǘ�
class DebugMenuFrame 
    : public DebugMenuLabel
{
    //  friends
    friend void DebugMenuLabel::attachSelf(t3::DebugMenuFrame &frame);
    friend void DebugMenuLabel::detachSelf();
    
public:
    ///
    /// �R���X�g���N�^
    DebugMenuFrame(
        DebugMenuFrame* parent, ///< �e
        const String& label     ///< �\����
    );
    
    ///
    /// �f�X�g���N�^
    ~DebugMenuFrame();

public:
    ///
    /// �t���[�����J��
    void openFrame();
    
    ///
    /// �t���[�������
    void closeFrame();
    
    ///
    /// �q�v�f�������Ă��邩����
    bool hasChild() const {
        return items_.size() > 0;
    }
    
    ///
    /// �t�H�[�J�X���̃A�C�e�����擾
    DebugMenuLabel* getFocusItem() {
        return focus_item_;
    }
    
    ///
    /// �t�H�[�J�X���̃A�C�e�����擾
    const DebugMenuLabel* getFocusItem() const {
        return focus_item_;
    }
    
    ///
    /// �t�H�[�J�X�A�C�e����ݒ�
    void setFocusItem(
        DebugMenuLabel* const item
    ){
        if (focus_item_) {
            focus_item_->unfocusCallback();
        }
        if (item) {
            item->focusCallback();
        }
        focus_item_ = item;
    }
    
    ///
    /// �A�C�e�����擾
    DebugMenuList& getItems() {
        return items_;
    }
    
    ///
    /// �A�C�e�����擾
    const DebugMenuList& getItems() const {
        return items_;
    }
    
    ///
    /// �X�V
    void update() override;
    
    ///
    /// �`��
    void drawFrame(
        const float x,
        const float y,
        const Color& color
    ) const;
    
    
private:
    ///
    /// �A�C�e�����A�^�b�`
    void attachItem(DebugMenuLabel& item);
    
    ///
    /// �A�C�e�����f�^�b�`
    void detachItem(DebugMenuLabel& item);
    
private:
    DebugMenuList items_;           ///< �q�A�C�e���ꗗ
    DebugMenuLabel* focus_item_;    ///< �t�H�[�J�X���̃A�C�e��
    int select_idx_;                ///< �I�𒆂̃C���f�b�N�X


};


}   // namespace t3

#endif // TRI_DEBUGMENU_FRAME_HPP_INCLUDED