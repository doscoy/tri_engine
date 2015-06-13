
#include "base/tri_scene.hpp"
#include "debug/tri_debugmenu.hpp"
#include "base/tri_event_manager.hpp"



TRI_CORE_NS_BEGIN



Scene::Scene(
    const char* const scene_name
)   : finish_(false)
    , show_task_(false)
    , scene_name_( scene_name )
    , scene_debug_menu_frame_(nullptr, scene_name)
    , dmi_show_task_(&scene_debug_menu_frame_, "show task", show_task_)
    , task_manager_()
{
    DebugMenu& debug_menu_root = DebugMenu::instance();

    scene_debug_menu_frame_.attachSelf(
        debug_menu_root.rootMenu()
    );
}

Scene::~Scene()
{
    scene_debug_menu_frame_.detachSelf();
}


void Scene::update(
    tick_t delta_time
) {
    task_manager_.updateTask(delta_time);
    updateScene(delta_time);
    
}

void Scene::suspend(
    tick_t delta_time
) {
    suspendScene(delta_time);
}

void Scene::debugRender() {
    if (show_task_) {
        task_manager_.printTask();
    }
    debugRenderScene();
}






    
SceneManager::SceneManager()
    : current_scene_( nullptr )
    , next_scene_generator_( nullptr )
    , force_change_( false )
    , scene_changed_( false )
{
    SceneGenerator* sg = Scene::sceneGenerator<NullScene>();
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

void SceneManager::debugRender() {
    current_scene_->debugRender();
}


void SceneManager::sceneChange()
{
    EventManagerBase::get()->dumpListeners();
    
    
    //  シーン終了
    //  後片付け
    const char* prev_scene_name = current_scene_->sceneName();
    current_scene_->terminateScene();

    //  次のシーンに遷移
    T3_TRACE_VALUE(current_scene_.use_count());
    current_scene_ = next_scene_generator_->createScene();
    next_scene_generator_ = Scene::sceneGenerator<NullScene>();
    
    EventManagerBase::get()->dumpListeners();

    //  シーン切り替え情報表示
    const char* next_scene_name = current_scene_->sceneName();
    T3_TRACE("scene change. %s --> %s\n", prev_scene_name, next_scene_name);
    (void)(prev_scene_name);
    (void)(next_scene_name);

    //  初期化
    current_scene_->initializeScene();

    //  シーンが切り替わったフラグON
    scene_changed_ = true;
    
    EventManagerBase::get()->dumpListeners();

}



void SceneManager::addSceneTask(
    SharedPtr<Task> task
) {
    instance().current_scene_->addSceneTask(task);
}

const TaskManager& SceneManager::taskManager() {
    return instance().current_scene_->taskManager();
}


TRI_CORE_NS_END

