

#include "tri_engine.hpp"
#include "samples.hpp"


#if CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_IOS
#include "ViewController.h"
#include "AppDelegate.h"
#endif


int main(int argc, char * argv[])
{
    {
        SampleApp app;
    //    app.rootScene(t3::SceneBase::sceneGenerator<RootTest>());
  
    //    app.rootScene(t3::SceneBase::sceneGenerator<InputTestScene>());
    //    app.rootScene(t3::SceneBase::sceneGenerator<UiButtonScene>());
    //      app.setRootScene(t3::SceneBase::sceneGenerator<QuatTestScene>());
    //    app.setRootScene(t3::SceneBase::sceneGenerator<ThreadTestScene>());
    //    app.rootScene(t3::SceneBase::sceneGenerator<BlurScene>());
    //    app.setRootScene(t3::SceneBase::sceneGenerator<AudioTestScene>());
    //    app.setRootScene(t3::SceneBase::sceneGenerator<ZipTestScene>());
    //    app.setRootScene(t3::SceneBase::sceneGenerator<MemPoolScene>());
    //    app.rootScene(t3::SceneBase::sceneGenerator<SimpleSpriteScene>());
    //    app.rootScene(t3::SceneBase::sceneGenerator<ColladaMeshScene>());
    //    app.rootScene(t3::SceneBase::sceneGenerator<SimpleMesh3Scene>());
    app.rootScene(t3::SceneBase::sceneGenerator<ShadowTestScene>());

        t3::setApplication(app);
    #if CROSS_TARGET_PLATFORM == CROSS_TARGET_PLATFORM_IOS
        @autoreleasepool {
            return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
        }
    }
    #else // MacOSX or Windows
        if (!t3::initializeTriEngine(800, 600, "win")) {
            //  初期化に失敗
            return 0;
        }
        t3::initializeApplication();

        while (t3::isActiveApplication()) {

            t3::updateApplication();
            t3::renderApplication();
        }
        t3::terminateApplication();
    }
    t3::terminateTriEngine();
#endif
    return 0;
}

