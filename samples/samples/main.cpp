//
//  main.m
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/03/19.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "tri_engine.hpp"
#include "samples.hpp"


#if defined(CROSS_TARGET_PLATFORM_IOS)
#include "ViewController.h"
#include "AppDelegate.h"
#endif

namespace t3 {

t3::MemoryPool* pool_ = nullptr;

void* heapAllocate(size_t size) {
    if (!pool_) {
        pool_ = new(std::malloc(sizeof(MemoryPool))) MemoryPool(1024*1024*20);
    }
    return pool_->allocate(size);
}

void heapDeallocate(void* addr) {
    pool_->deallocate(addr);
}

}   // t3


class RootTest
    : public t3::Scene
{
public:
    RootTest()
        : Scene("RootTest")
        , sandbox_(0, "SANDBOX")
        , dmsl_simple_sprite_(&sandbox_, "SIMPLE SPRITE")
//        , dmsl_audio_test_(&sandbox_, "AUDIO TEST")
//        , dmsl_ad_test_(&sandbox_, "AD TEST")
//        , dmsl_event_handling_(&sandbox_, "EVENT HANDLING")
//        , dmsl_mesh_obj_(&sandbox_, "MESH OBJ")
    {}

public:
    void initializeScene() override {
        t3::DebugMenu& dm = t3::DebugMenu::instance();
        sandbox_.attachSelf(dm.rootMenu());
    }

    void updateScene(t3::tick_t delta_time) override {
        t3::printDisplay(
            0,
            100,
            t3::color_sample::white(),
            "%d",
            t3::frame_counter_.now()
            );

        auto& d = t3::Director::instance();
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
//    t3::DebugMenuSceneLouncher<AudioTestScene> dmsl_audio_test_;
//    t3::DebugMenuSceneLouncher<AdScene> dmsl_ad_test_;
//    t3::DebugMenuSceneLouncher<EventHandlingScene> dmsl_event_handling_;
//    t3::DebugMenuSceneLouncher<MeshObjScene> dmsl_mesh_obj_;

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

int main(int argc, char * argv[])
{
    int a= 30;
    SampleApp app;
    
//    app.setRootScene(t3::Scene::sceneGenerator<UiButtonScene>());
//      app.setRootScene(t3::Scene::sceneGenerator<QuatTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<ThreadTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<OffscreenTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<AudioTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<ZipTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<MemPoolScene>());
    app.rootScene(t3::Scene::sceneGenerator<SimpleSpriteScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<FontTestScene>());


    t3::setApplication(app);
#if defined(CROSS_TARGET_PLATFORM_IOS)
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
#else
    t3::initializeTriEngine(640, 480, "win");
    t3::initializeApplication();

#endif
    return 0;
}

