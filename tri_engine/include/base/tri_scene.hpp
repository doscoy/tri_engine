

#ifndef TRI_SCENE_HPP_INCLUDED
#define TRI_SCENE_HPP_INCLUDED

#include "dbg/tri_debugmenu.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_singleton.hpp"
#include "base/tri_types.hpp"
#include <memory>
#include "dbg/tri_trace.hpp"

#include "tri_task_manager.hpp"



namespace t3 {
inline namespace base {

class Scene;
class SceneGenerator
{
public:
    virtual ~SceneGenerator(){}
    virtual std::shared_ptr<Scene> createScene() = 0;
};


template <typename T>
class TypedSceneGenerator
    : public SceneGenerator
{
    typedef TypedSceneGenerator<T>  self_t;
    typedef T                       scene_t;
public:
    
    //  インスタンス取得
    static self_t* getInstancePtr() {
        static self_t instance_;
        return &instance_;
    }
    
    
    //  シーン生成
    std::shared_ptr<Scene> createScene() override {
        return std::shared_ptr<Scene>(T3_NEW scene_t);
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
    virtual void initializeScene(){};
    virtual void terminateScene(){};
    virtual void updateScene(tick_t){};
    virtual void suspendScene(tick_t){};
    
public:
    void update(tick_t delta_time);
    void suspend(tick_t delta_time);
    
    bool isFinished() const {
        return finish_;
    };
    
    const char* getSceneName() const {
        return scene_name_;
    }

    DebugMenuFrame& getSceneDebugMenuFrame() {
        return scene_debug_menu_frame_;
    }
    
    template <typename SceneType>
    static SceneGenerator* getSceneGenerator(){
        return TypedSceneGenerator<SceneType>::getInstancePtr();
    }

    void addSceneTask(std::shared_ptr<Task> task) {
        task_manager_.attach(task);
    }


protected:
    void setFinish(bool f) {
        finish_ = f;
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
    friend class Singleton;
    
private:
    SceneManager();
    ~SceneManager();
    
public:
    void updateScene( tick_t delta_time );
    void suspendScene( tick_t delta_time );
    
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
        std::shared_ptr<Task> task
    );

private:
    void sceneChange();

private:
    std::shared_ptr<Scene> current_scene_;
    SceneGenerator* next_scene_generator_;
    bool force_change_;
    bool scene_changed_;
};


}   // namespace base

}   // namespace t3

#endif // TRI_SCENE_HPP_INCLUDED

