////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
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
#include "core/debug/tri_trace.hpp"
#include "core/base/tri_task.hpp"
#include "core/base/tri_director.hpp"


TRI_CORE_NS_BEGIN



class SceneBase;
using ScenePtr = SharedPtr<SceneBase>;

class SceneGenerator
{
public:
    virtual ~SceneGenerator(){}
    virtual ScenePtr createScene() = 0;
};


template <typename T>
class TypedSceneGenerator
    : public SceneGenerator
{

    using GenType = T;
    using SelfType = TypedSceneGenerator<T>;
public:
    
    //  インスタンス取得
    static SelfType* instancePtr() {
        static SelfType instance_;
        return &instance_;
    }
    
    //  シーン生成
    ScenePtr createScene() override {
        return Director::instance().rootTask()->createTask<GenType>();

    }
};


class SceneBase
    : public TaskBase
{
    friend class SceneGenerator;
    friend class SceneManager;
public:
    explicit SceneBase(
        const char* const scene_name 
    );
    virtual ~SceneBase();

public:
    virtual void initializeScene() {}
    virtual void terminateScene() {}
    virtual void updateScene(const DeltaTime) {}
    virtual void debugRenderScene() {}

public:
    void onTaskFirstUpdate() override;
    void onTaskUpdate(const DeltaTime dt) override;
    void onTaskKill() override;
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

protected:
    void finish() {
        finish_ = true;
    }

private:
    bool finish_;
    const char* scene_name_;
    DebugMenuFrame scene_debug_menu_frame_;
};



class NullScene
    : public SceneBase
{
public:
    NullScene()
        : SceneBase("NullScene")
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
    void initialize();

    void debugRender();
    
    static void requestNextScene(
        SceneGenerator* const next_scene_generator
    ) {
        instance().next_scene_generator_ = next_scene_generator;
    }
    
    void forceChangeScene(
        SceneGenerator* const next_scene_generator
    ) {
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

private:
    void sceneChange();

private:
    ScenePtr current_scene_;
    SceneGenerator* next_scene_generator_;
    bool force_change_;
    bool scene_changed_;
};



TRI_CORE_NS_END

#endif // TRI_SCENE_HPP_INCLUDED

