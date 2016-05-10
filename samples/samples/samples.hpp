////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#ifndef SAMPLES_HPP_INCLUDED
#define SAMPLES_HPP_INCLUDED

//  includes
#include "tri_engine.hpp"

#include "simple_sprite/simple_sprite.hpp"
#include "simple_primitive/simple_primitive.hpp"
#include "input/input_test.hpp"
#include "collada_mesh/collada_mesh.hpp"
#include "collada_mesh2/collada_mesh2.hpp"
#include "blur/blur_test.hpp"
//#include "event_handling/event_handling.hpp"
#include "simple_mesh/simple_mesh.hpp"
#include "simple_mesh2/simple_mesh2.hpp"
#include "simple_mesh3/simple_mesh3.hpp"
//#include "mem_pool/mem_pool_test.hpp"
#include "ui_button/ui_button_test.hpp"
//#include "quat/quat_test_scene.hpp"
//#include "offscreen/offscreen_test.hpp"
//#include "thread/thread_test.hpp"
//#include "zipfile/zip_test.hpp"
//#include "blur/blur_test.hpp"
//#include "font/font_test.hpp"
#include "shadow/shadow_test.hpp"
#include "web_notification/web_notification_test.hpp"


class RootTest
    : public t3::SceneBase
{
public:
    RootTest()
        : SceneBase("RootTest")
        , samples_(0, "SAMPLES")
        , simple_primitive_(&samples_, "SIMPLE PRIMITIVE")
        , simple_sprite_(&samples_, "SIMPLE SPRITE")
        , input_test_(&samples_, "INPUT TEST")
        , blur_test_(&samples_, "BLUR TEST")
        , collada_mesh_(&samples_, "COLLADA_MESH")
        , simple_mesh1_(&samples_, "SIMPLE MESH1")
        , simple_mesh2_(&samples_, "SIMPLE MESH2")
        , simple_mesh3_(&samples_, "SIMPLE MESH3")
        , shadow_test(&samples_, "SHADOW TEST")
        , web_notification_test_(&samples_, "WEB NOTIFICATION TEST")
    {}

public:
    void initializeScene() override {
        auto& dm = t3::DebugMenu::instance();
        samples_.attachSelf(dm.rootMenu());
    }

    void updateScene(const t3::FrameInfo& frame_info) override {
        T3_PRINT_DISP(
            0,
            100,
            "%d",
            t3::frame_counter_.now()
        );

    }

    void terminateScene() override {
        samples_.detachSelf();
    }


private:
    t3::DebugMenuFrame samples_;
    t3::DebugMenuSceneLouncher<SimplePrimitiveScene> simple_primitive_;
    t3::DebugMenuSceneLouncher<SimpleSpriteScene> simple_sprite_;
    t3::DebugMenuSceneLouncher<InputTestScene> input_test_;
    t3::DebugMenuSceneLouncher<BlurScene> blur_test_;
    t3::DebugMenuSceneLouncher<ColladaMeshScene> collada_mesh_;
    t3::DebugMenuSceneLouncher<SimpleMeshScene>  simple_mesh1_;
    t3::DebugMenuSceneLouncher<SimpleMesh2Scene> simple_mesh2_;
    t3::DebugMenuSceneLouncher<SimpleMesh3Scene> simple_mesh3_;
    t3::DebugMenuSceneLouncher<ShadowTestScene> shadow_test;
    t3::DebugMenuSceneLouncher<WebNotificationTest> web_notification_test_;
};


class SampleApp
    : public t3::Application
{
    //  ゲームの初期化
    void initializeGame() override {
        auto& sm = t3::SceneManager::instance();

        //    app.rootScene(t3::SceneBase::sceneGenerator<RootTest>());
  
        //    app.rootScene(t3::SceneBase::sceneGenerator<InputTestScene>());
        //    app.rootScene(t3::SceneBase::sceneGenerator<UiButtonScene>());
        //      app.setRootScene(t3::SceneBase::sceneGenerator<QuatTestScene>());
        //    app.setRootScene(t3::SceneBase::sceneGenerator<ThreadTestScene>());
        //    app.rootScene(t3::SceneBase::sceneGenerator<BlurScene>());
        //    app.setRootScene(t3::SceneBase::sceneGenerator<AudioTestScene>());
        //    app.setRootScene(t3::SceneBase::sceneGenerator<ZipTestScene>());
        //    app.setRootScene(t3::SceneBase::sceneGenerator<MemPoolScene>());
        //    app.rootScene(t3::TaskGenerator<ColladaMeshScene>::instancePtr());
        //    app.rootScene(t3::TaskGenerator<ColladaMesh2Scene>::instancePtr());
        
        //app.rootScene(t3::TaskGenerator<WebNotificationTest>::instancePtr());
    
//        sm.rootScene(t3::TaskGenerator<SimpleSpriteScene>::instancePtr());
//        sm.rootScene(t3::TaskGenerator<SimpleMesh3Scene>::instancePtr());
//        sm.rootScene(t3::TaskGenerator<ShadowTestScene>::instancePtr());
        sm.rootScene(t3::TaskGenerator<BlurScene>::instancePtr());
        
    }
    
    
    //  ゲームの後片付け
    void terminateGame() override {
        
        
    }
};


#endif
