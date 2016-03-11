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


///
/// メインシーンの基底
/// メインシーンはアプリケーションの中で同時に１つしか存在できない
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
    
    
    const char* sceneName() const {
        return scene_name_;
    }

    DebugMenuFrame& sceneDebugMenuFrame() {
        return scene_debug_menu_frame_;
    }


protected:
    void finish() {
        killTask();
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
    ///
    /// 強制シーン切り替え
    void forceChangeScene(
        TaskGeneratorBase* const next_scene_generator
    ) {
        if (cur_) {
            cur_->nextTaskGenerator(next_scene_generator);
            cur_->killTask();
        }
    }
    
    ///
    /// 強制ルートシーンへ
    void restart() {
        forceChangeScene(root_scene_generator_);
    }


    ///
    /// シーン切り替え完了判定
    bool isSceneChenged() const {
        return scene_changed_;
    }
    
    ///
    /// カレントシーン設定
    void current(SceneBase* s) {
        T3_ASSERT_MSG(cur_ == nullptr || s == nullptr, "Scene instance must only one in frame.");
        cur_ = s;
    }

    ///
    /// シーン切り替え順登録
    void addSceneHistory(const char* const name) {
        history_.push_back(name);
    }

    ///
    /// アプリケーションのルートシーンを設定
    void rootScene(
        TaskGeneratorBase* root    ///< root
    ) {
        root_scene_generator_ = root;
    }

    TaskGeneratorBase* rootScene() const {
        return root_scene_generator_;
    }
    
private:
    ///
    /// カレントシーン
    SceneBase* cur_;

    ///
    /// シーン切り替え完了フラグ
    bool scene_changed_;

    ///
    /// シーンヒストリ
    Vector<const char*> history_;

    ///
    /// ルートシーン
    TaskGeneratorBase* root_scene_generator_;
};

///
/// ブートシーン
class BootScene
    : public SceneBase
{
public:
    BootScene()
        : SceneBase("BootScene")
    {}

    
    void initializeScene() override {
        auto& sm = SceneManager::instance();
        nextTaskGenerator(sm.rootScene());
    }

    void updateScene(const DeltaTime dt) override {
        finish();
    }
};




TRI_CORE_NS_END

#endif // TRI_SCENE_HPP_INCLUDED

