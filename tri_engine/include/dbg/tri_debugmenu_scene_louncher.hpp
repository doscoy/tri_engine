
#ifndef TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED
#define TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED

//  include
#include "base/tri_scene.hpp"

namespace t3 {

///
/// デバッグメニュー.
/// シーンランチャ
template <class T>
class DebugMenuSceneLouncher
    : public DebugMenuLabel
{
public:
    ///
    /// コンストラクタ
    DebugMenuSceneLouncher(
        DebugMenuFrame* parent, ///< 親フレーム
        const char* const label ///< ラベル
    )   : DebugMenuLabel(parent, label)
    {}

public:
    ///
    /// 更新処理
    void update() override {

        const auto& pad = debugPad();
        //  フォーカスされて決定したら登録してあるシーンに強制的に飛ばす
        if (pad.isTrigger(Pad::BUTTON_A)) {
            auto& sm = SceneManager::instance();
            sm.forceChangeScene(gen_.instancePtr());
        }
        else if (pad.isTrigger(Pad::BUTTON_B)) {
            parent_->setFocusItem(nullptr);
        }

    }
    TypedSceneGenerator<T> gen_;    ///< 切り替えるシーン
};

}   //  namespace t3

#endif  // TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED
