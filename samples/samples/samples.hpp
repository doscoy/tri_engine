//
//  sandbox.hpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/01/25.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#ifndef SAMPLES_HPP_INCLUDED
#define SAMPLES_HPP_INCLUDED

#include "tri_engine.hpp"

#include "sprite/simple_sprite.hpp"
#include "audio/audio_test.hpp"
#include "ad/ad_test.hpp"
#include "event_handling/event_handling.hpp"
#include "mesh_obj/mesh_obj_scene.hpp"
#include "ui_button/ui_button_test.hpp"
#include "quat/quat_test_scene.hpp"

#include "thread/thread_test.hpp"


class RootTest
    : public t3::Scene
{
public:
    RootTest()
    : Scene("RootTest")
    , sandbox_(0, "SANDBOX")
    , dmsl_simple_sprite_(&sandbox_, "SIMPLE SPRITE")
    , dmsl_audio_test_(&sandbox_, "AUDIO TEST")
    , dmsl_ad_test_(&sandbox_, "AD TEST")
    , dmsl_event_handling_(&sandbox_, "EVENT HANDLING")
    , dmsl_mesh_obj_(&sandbox_, "MESH OBJ")
    {}
    
public:
    void initializeScene() override {
        t3::DebugMenu& dm = t3::DebugMenu::instance();
        sandbox_.attachSelf(dm.getMenuRoot());
    }
    
    void updateScene(t3::tick_t delta_time) override {
        t3::printDisplay(
            0,
            100,
            t3::Color::white(),
            "%d",
            t3::frame_counter_.now()
        );
        
        t3::Director& d = t3::Director::instance();
        const t3::Input& input = d.input();
        
        if (input.pointing().isDoubleClick()) {
            T3_TRACE("Double Click.\n");
        }
    }
    
    void terminateScene() override {
        sandbox_.detachSelf();
    }
    
    
private:
    t3::DebugMenuFrame sandbox_;
    t3::DebugMenuSceneLouncher<SimpleSpriteScene> dmsl_simple_sprite_;
    t3::DebugMenuSceneLouncher<AudioTestScene> dmsl_audio_test_;
    t3::DebugMenuSceneLouncher<AdScene> dmsl_ad_test_;
    t3::DebugMenuSceneLouncher<EventHandlingScene> dmsl_event_handling_;
    t3::DebugMenuSceneLouncher<MeshObjScene> dmsl_mesh_obj_;
    
};


#endif
