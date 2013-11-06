
#include "tri_scene.hpp"
#include "tri_develop_base.hpp"
#include "../dbg/tri_debugmenu.hpp"

namespace t3{


Scene::Scene(
    const char* const scene_name
)   : finish_(false)
    , scene_name_( scene_name )
    , scene_debug_menu_frame_(nullptr, scene_name)
{
    DebugMenu& debug_menu_root = DebugMenu::getInstance();

    scene_debug_menu_frame_.attachSelf(
        debug_menu_root.getMenuRoot()
    );
}

Scene::~Scene()
{
    scene_debug_menu_frame_.detachSelf();
}











    
SceneManager::SceneManager()
    : current_scene_( nullptr )
    , next_scene_generator_( nullptr )
    , force_change_( false )
    , scene_changed_( false )
{
    SceneGenerator* sg = getSceneGenerator<NullScene>();
    current_scene_ = sg->createScene();
}


SceneManager::~SceneManager()
{
    
    
}


void SceneManager::updateScene(
    tick_t tick
){
    current_scene_->updateScene( tick );
}


void SceneManager::directScene()
{
    if ( current_scene_->isFinished() || force_change_ ){
        force_change_ = false;
        sceneChange();
    }
    else {
        scene_changed_ = false;
    }
}

void SceneManager::suspendScene(
    tick_t tick
){
    current_scene_->suspendScene( tick );
}


void SceneManager::sceneChange()
{

    //  シーン終了
    //  後片付け
    const char* prev_scene_name = current_scene_->getSceneName();
    current_scene_->terminateScene();

    //  次のシーンに遷移
    T3_TRACE_VALUE(current_scene_.use_count());
    current_scene_ = next_scene_generator_->createScene();
    next_scene_generator_ = getSceneGenerator<NullScene>();
    
    
    //  初期化
    current_scene_->initializeScene();
    const char* next_scene_name = current_scene_->getSceneName();

    //  シーンが切り替わったフラグON
    scene_changed_ = true;
    
    T3_TRACE( "scene change. %s --> %s", prev_scene_name, next_scene_name );

}




}   // namespace t3