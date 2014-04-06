//
//  main.m
//  tri_samples_ios
//
//  Created by KANI Tetsuro on 2014/03/19.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#include "tri_engine.hpp"
#include "samples.hpp"

int main(int argc, char * argv[])
{
    t3::Application app(t3::Scene::getSceneGenerator<RootTest>());
//    t3::Application app(t3::Scene::getSceneGenerator<SimpleSpriteScene>());
    t3::platform::run(argc, argv, &app);

    return 0;
}
