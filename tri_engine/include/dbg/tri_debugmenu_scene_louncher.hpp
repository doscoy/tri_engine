
#ifndef TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED
#define TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED

//  include
#include "base/tri_scene.hpp"

namespace t3 {

///
/// �f�o�b�O���j���[.
/// �V�[�������`��
template <class T>
class DebugMenuSceneLouncher
    : public DebugMenuLabel
{
public:
    ///
    /// �R���X�g���N�^
    DebugMenuSceneLouncher(
        DebugMenuFrame* parent, ///< �e�t���[��
        const char* const label ///< ���x��
    )   : DebugMenuLabel(parent, label)
    {}

public:
    ///
    /// �X�V����
    void update() override {

        const auto& pad = debugPad();
        //  �t�H�[�J�X����Č��肵����o�^���Ă���V�[���ɋ����I�ɔ�΂�
        if (pad.isTrigger(Pad::BUTTON_A)) {
            auto& sm = SceneManager::instance();
            sm.forceChangeScene(gen_.instancePtr());
        }
        else if (pad.isTrigger(Pad::BUTTON_B)) {
            parent_->setFocusItem(nullptr);
        }

    }
    TypedSceneGenerator<T> gen_;    ///< �؂�ւ���V�[��
};

}   //  namespace t3

#endif  // TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED
