
#ifndef SAMPLES_HPP_INCLUDED
#define SAMPLES_HPP_INCLUDED

//  includes
#include "tri_engine.hpp"

#include "simple_sprite/simple_sprite.hpp"
#include "simple_primitive/simple_primitive.hpp"
#include "input/input_test.hpp"
//#include "audio/audio_test.hpp"
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
//        , dmsl_event_handling_(&sandbox_, "EVENT HANDLING")
        , simple_mesh1_(&samples_, "SIMPLE MESH1")
        , simple_mesh2_(&samples_, "SIMPLE MESH2")
        , simple_mesh3_(&samples_, "SIMPLE MESH3")
        , shadow_test(&samples_, "SHADOW TEST")
    {}

public:
    void initializeScene() override {
        auto& dm = t3::DebugMenu::instance();
        samples_.attachSelf(dm.rootMenu());
    }

    void updateScene(t3::tick_t delta_time) override {
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
//    t3::DebugMenuSceneLouncher<EventHandlingScene> dmsl_event_handling_;
    t3::DebugMenuSceneLouncher<SimpleMeshScene>  simple_mesh1_;
    t3::DebugMenuSceneLouncher<SimpleMesh2Scene> simple_mesh2_;
    t3::DebugMenuSceneLouncher<SimpleMesh3Scene> simple_mesh3_;
    t3::DebugMenuSceneLouncher<ShadowTestScene> shadow_test;

};


class SampleApp
    : public t3::Application
{
    //  ゲームの初期化
    void initializeGame() override {
        
        
    }
    
    
    //  ゲームの後片付け
    void terminateGame() override {
        
        
    }
};


#endif
