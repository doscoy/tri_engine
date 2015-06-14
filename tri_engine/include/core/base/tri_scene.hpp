/**
    @file tri_scene.hpp
    シーン.
*/

#ifndef TRI_SCENE_HPP_INCLUDED
#define TRI_SCENE_HPP_INCLUDED


#include "core/core_config.hpp"
#include "core/debug/tri_debugmenu.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/utility/tri_singleton.hpp"
#include "core/base/tri_types.hpp"
#include "core/base/tri_std.hpp"
#include "core/debug/tri_trace.hpp"

#include "tri_task_manager.hpp"



TRI_CORE_NS_BEGIN



class Scene;
class SceneGenerator
{
public:
    virtual ~SceneGenerator(){}
    virtual SharedPtr<Scene> createScene() = 0;
};


template <typename T>
class TypedSceneGenerator
    : public SceneGenerator
{
    typedef TypedSceneGenerator<T>  self_t;
    typedef T                       scene_t;
public:
    
    //  インスタンス取得
    static self_t* instancePtr() {
        static self_t instance_;
        return &instance_;
    }
    
    
    //  シーン生成
    SharedPtr<Scene> createScene() override {
        return SharedPtr<Scene>(T3_SYS_NEW scene_t);
    }

};


class Scene
    : private Uncopyable
{
    friend class SceneGenerator;
    
public:
    explicit Scene(
        const char* const scene_name 
    );
    virtual ~Scene();

public:
    virtual void initializeScene(){}
    virtual void terminateScene(){}
    virtual void updateScene(tick_t){}
    virtual void suspendScene(tick_t){}
    virtual void debugRenderScene(){}

public:
    void update(tick_t delta_time);
    void suspend(tick_t delta_time);
    void debugRender();
    
    bool isFinished() const {
        return finish_;
    };
    
    const char* sceneName() const {
        return scene_name_;
    }

    DebugMenuFrame& sceneDebugMenuFrame() {
        return scene_debug_menu_frame_;
    }
    
    template <typename SceneType>
    static SceneGenerator* sceneGenerator(){
        return TypedSceneGenerator<SceneType>::instancePtr();
    }

    void addSceneTask(SharedPtr<Task> task) {
        task_manager_.attach(task);
    }

    const TaskManager& taskManager() const {
        return task_manager_;
    }
    
protected:
    void finish() {
        finish_ = true;
    }

private:
    bool finish_;
    bool show_task_;
    const char* scene_name_;
    DebugMenuFrame scene_debug_menu_frame_;
    DebugMenuItem<bool> dmi_show_task_;
    TaskManager task_manager_;
};



class NullScene
    : public Scene
{
public:
    NullScene()
        : Scene( "NullScene" )
    {}
};



class SceneManager
    : public Singleton<SceneManager>
{
    friend class Singleton<SceneManager>;
    
private:
    SceneManager();
    ~SceneManager();
    
public:
    void updateScene( tick_t delta_time );
    void suspendScene( tick_t delta_time );
    void debugRender();
    
    static void requestNextScene( SceneGenerator* const next_scene_generator ){
        instance().next_scene_generator_ = next_scene_generator;
    }
    
    void forceChangeScene( SceneGenerator* const next_scene_generator ){
        next_scene_generator_ = next_scene_generator;
        force_change_ = true;
    }
    
    bool isSceneChenged() const {
        return scene_changed_;
    }
    
    bool isForceChangeRequested() const {
        return force_change_;
    }
    
    void directScene();

public:
    static void addSceneTask(
        SharedPtr<Task> task
    );

    static const TaskManager& taskManager();

private:
    void sceneChange();

private:
    SharedPtr<Scene> current_scene_;
    SceneGenerator* next_scene_generator_;
    bool force_change_;
    bool scene_changed_;
};



TRI_CORE_NS_END

#endif // TRI_SCENE_HPP_INCLUDED

