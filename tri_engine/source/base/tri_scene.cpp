
#include "tri_scene.hpp"
#include "dbg/tri_debugmenu.hpp"

namespace t3 {
inline namespace base {

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


void Scene::update(
    tick_t delta_time
) {
//    t3::printDisplay(0, 0, "task %d", task_manager_.getTaskCount());
    task_manager_.updateTask(delta_time);
    updateScene(delta_time);
}

void Scene::suspend(
    tick_t delta_time
) {
    suspendScene(delta_time);
}








    
SceneManager::SceneManager()
    : current_scene_( nullptr )
    , next_scene_generator_( nullptr )
    , force_change_( false )
    , scene_changed_( false )
{
    SceneGenerator* sg = Scene::getSceneGenerator<NullScene>();
    current_scene_ = sg->createScene();
}


SceneManager::~SceneManager()
{
    
    
}


void SceneManager::updateScene(
    tick_t delta_time
){
    current_scene_->update(delta_time);
}


void SceneManager::directScene()
{
    if (current_scene_->isFinished() || force_change_) {
        force_change_ = false;
        sceneChange();
    }
    else {
        scene_changed_ = false;
    }
}

void SceneManager::suspendScene(
    tick_t delta_time
){
    current_scene_->suspend(delta_time);
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
    next_scene_generator_ = Scene::getSceneGenerator<NullScene>();
    
    
    //  初期化
    current_scene_->initializeScene();
    const char* next_scene_name = current_scene_->getSceneName();

    //  シーンが切り替わったフラグON
    scene_changed_ = true;
    
    T3_TRACE("scene change. %s --> %s\n", prev_scene_name, next_scene_name);
    (void)(prev_scene_name);
    (void)(next_scene_name);
}



void SceneManager::addSceneTask(
    std::shared_ptr<Task> task
) {
    getInstance().current_scene_->addSceneTask(task);
}

}   // namespace base
}   // namespace t3

