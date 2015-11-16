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
}

SceneBase::~SceneBase() {
    scene_debug_menu_frame_.detachSelf();
}



void SceneBase::taskInitialize() {
    initializeScene();
}

void SceneBase::taskUpdate(
    const DeltaTime delta_time
) {
    updateScene(delta_time);
}

void SceneBase::taskTerminate() {
    terminateScene();
}

void SceneBase::debugRender() {
    debugRenderScene();
}






    
SceneManager::SceneManager()
    : current_scene_(nullptr)
    , next_scene_generator_(nullptr)
    , force_change_(false)
    , scene_changed_(false)
{
}


SceneManager::~SceneManager() {
    
}

void SceneManager::initialize() {
    SceneGenerator* sg = SceneBase::sceneGenerator<NullScene>();
    current_scene_ = sg->createScene();
}

void SceneManager::directScene() {
    if (current_scene_->isFinished() || force_change_) {
        force_change_ = false;
        sceneChange();
    }
    else {
        scene_changed_ = false;
    }
}


void SceneManager::debugRender() {
    current_scene_->debugRender();
}


void SceneManager::sceneChange() {
    T3_RENDER_ASSERT();
    EventManager::dumpListeners();
    
    //  シーン終了
    //  後片付け
    const char* prev_scene_name = current_scene_->sceneName();

    //  次のシーンに遷移
    current_scene_->killTask();
    current_scene_ = next_scene_generator_->createScene();
    next_scene_generator_ = SceneBase::sceneGenerator<NullScene>();
    
    EventManager::dumpListeners();

    //  シーン切り替え情報表示
    const char* next_scene_name = current_scene_->sceneName();
    T3_SYSTEM_LOG("scene change. %s --> %s\n", prev_scene_name, next_scene_name);
    (void)(prev_scene_name);
    (void)(next_scene_name);

    //  シーンが切り替わったフラグON
    scene_changed_ = true;
    
    EventManager::dumpListeners();

}




TRI_CORE_NS_END

