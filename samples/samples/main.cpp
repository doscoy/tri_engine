

#include "tri_engine.hpp"
#include "samples.hpp"


#if defined(CROSS_TARGET_PLATFORM_IOS)
#include "ViewController.h"
#include "AppDelegate.h"
#endif


int main(int argc, char * argv[])
{
    SampleApp app;
    app.rootScene(t3::Scene::sceneGenerator<RootTest>());
  
//    app.rootScene(t3::Scene::sceneGenerator<InputTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<UiButtonScene>());
//      app.setRootScene(t3::Scene::sceneGenerator<QuatTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<ThreadTestScene>());
//    app.rootScene(t3::Scene::sceneGenerator<BlurScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<AudioTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<ZipTestScene>());
//    app.setRootScene(t3::Scene::sceneGenerator<MemPoolScene>());
//    app.rootScene(t3::Scene::sceneGenerator<SimpleSpriteScene>());
    app.rootScene(t3::Scene::sceneGenerator<ShadowTestScene>());

    t3::setApplication(app);
#if defined(CROSS_TARGET_PLATFORM_IOS)
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
#else // MacOSX or Windows
    t3::initializeTriEngine(150, 150, "win");
    t3::initializeApplication();

    while (t3::isActiveApplication()) {

        t3::updateApplication();
        t3::renderApplication();
    }
    t3::terminateApplication();
    t3::terminateTriEngine();
#endif
    return 0;
}

