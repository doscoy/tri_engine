//
//  main.m
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/03/19.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "tri_engine.hpp"
#include "samples.hpp"



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
    app.setRootScene(t3::Scene::sceneGenerator<ZipTestScene>());

    t3::platform::run(argc, argv, &app);

    return 0;
}

