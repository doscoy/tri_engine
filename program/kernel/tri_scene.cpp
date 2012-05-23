
#include "tri_scene.hpp"
#include "tri_develop_base.hpp"


namespace t3{
    
    
SceneManager::SceneManager()
    : current_scene_( nullptr )
    , next_scene_generator_( nullptr )
    , force_change_( false )
    , scene_changed_( false )
{
    SceneGenerator* sg = getSceneGenerator<NullScene>();
    current_scene_.reset( sg->createScene() );
}


SceneManager::~SceneManager()
{
    
    
}


void SceneManager::updateScene(
    tick_t tick
){
    current_scene_->updateScene( tick );
    
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
    current_scene_.reset( next_scene_generator_->createScene() );
    next_scene_generator_ = getSceneGenerator<NullScene>();
    
    
    //  初期化
    current_scene_->initializeScene();
    const char* next_scene_name = current_scene_->getSceneName();

    //  シーンが切り替わったフラグON
    scene_changed_ = true;
    
    T3_TRACE( "scene change. %s --> %s", prev_scene_name, next_scene_name );

}




}   // namespace t3