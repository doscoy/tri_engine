////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "tri_engine.hpp"
#include "samples.hpp"


#if CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_IOS
#include "ViewController.h"
#include "AppDelegate.h"
#endif


int main(int argc, char * argv[])
{
    
    auto& tri = t3::Framework::createInstance();

    tri.setApplication(t3::Application::getGenerator<SampleApp>());
#if CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_IOS
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
    
#else // MacOSX or Windows
    float screen_x = 16 * 10;
    float screen_y =  9 * 10;
    if (!tri.initializeFramework(screen_x, screen_y, "win")) {
        //  初期化に失敗
        return 0;
    }
        
    while (tri.isActive()) {
        tri.updateFramework();
        tri.renderFramework();
    }
    tri.terminateFramework();
    
#endif
    return 0;
}

