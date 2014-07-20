
#ifndef TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED
#define TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED


#include "base/tri_scene.hpp"

namespace t3 {
inline namespace dbg {


template <class T>
class DebugMenuSceneLouncher
    : public DebugMenuLabel
{
public:
    DebugMenuSceneLouncher(
        DebugMenuFrame* parent,
        const char* const label
    )   : DebugMenuLabel(parent, label)
    {
    }

public:
    void update() override {

        const Pad& pad = debugPad();
        if (pad.isTrigger(Pad::BUTTON_A)) {
            SceneManager& sm = SceneManager::instance();
            sm.forceChangeScene( gen_.getInstancePtr() );
        }
        else if (pad.isTrigger(Pad::BUTTON_B)) {
            parent_->setFocusItem(nullptr);
        }

    }
    TypedSceneGenerator<T> gen_;
};


}   //  namespace dbg
}   //  namespace t3

#endif  // TRI_DEBUGMENU_SCENE_LOUNCHER_HPP_INCLUDED
