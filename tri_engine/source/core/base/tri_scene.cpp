////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/base/tri_scene.hpp"
#include "core/debug/tri_debugmenu.hpp"
#include "core/base/tri_event_manager.hpp"



TRI_CORE_NS_BEGIN



SceneBase::SceneBase(
    const char* const scene_name
)   : TaskBase()
    , finish_(false)
    , scene_name_(scene_name)
    , scene_debug_menu_frame_(nullptr, scene_name)
{
    DebugMenu& debug_menu_root = DebugMenu::instance();

    scene_debug_menu_frame_.attachSelf(
        debug_menu_root.rootMenu()
    );
    
    
    SceneManager::instance().current(this);
    SceneManager::instance().addSceneHistory(scene_name);
}

SceneBase::~SceneBase() {
    scene_debug_menu_frame_.detachSelf();
    SceneManager::instance().current(nullptr);
}



void SceneBase::onTaskFirstUpdate() {
    initializeScene();
}

void SceneBase::onTaskUpdate(
    const FrameInfo& frame_info
) {
    updateScene(frame_info);
}

void SceneBase::onTaskKill() {
    terminateScene();
}

void SceneBase::debugRender() {
    debugRenderScene();
}




    
SceneManager::SceneManager()
    : cur_(nullptr)
    , scene_changed_(false)
{
}


SceneManager::~SceneManager() {
}







TRI_CORE_NS_END

