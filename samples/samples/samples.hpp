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

#include "simple_sprite/simple_sprite.hpp"
#include "audio_test/audio_test.hpp"
#include "ad_test/ad_test.hpp"

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
    {}
    
public:
    void initializeScene() override {
        t3::DebugMenu& dm = t3::DebugMenu::getInstance();
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
        
        t3::GameSystem& game_system = t3::GameSystem::getInstance();
        const t3::Input& input = game_system.getInput();
        
        if (input.getPointing().isDoubleClick()) {
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
    
};


#endif
