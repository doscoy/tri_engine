//
//  main.m
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/03/19.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "tri_engine.hpp"
#include "samples.hpp"


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
    SampleApp app;
    
//    app.setRootScene(t3::Scene::sceneGenerator<UiButtonScene>());
//      app.setRootScene(t3::Scene::sceneGenerator<QuatTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<ThreadTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<OffscreenTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<AudioTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<ZipTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<MemPoolScene>());

    app.setRootScene(t3::Scene::sceneGenerator<SimpleSpriteScene>());

    t3::platform::run(argc, argv, &app);

    return 0;
}

