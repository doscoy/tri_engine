

#include "zip_test.hpp"


class ZipTestScene::SceneContext {


public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        t3::FilePath path = "test.zip";
        t3::ZipFile zip;
        bool init_res = zip.initialize(path.getFullPath());
        
        if (!init_res) {
            return;
        }
        
        //  初期化成功
        for (int i = 0; i < zip.entries(); ++i) {
            T3_TRACE("%d>%s %d\n",
                i,
                zip.getFileName(i).c_str(),
                zip.getFileSize(i)
            );
        }
        
        char buf[9999];
        std::string hog("hog/stamp.png");
        zip.readFile(hog, buf);
        
        
//        t3::TexturePtr tex = t3::TextureFactory::createFromPngFile(buf);
//        sp_layer_.createSprite(tex);
        
        
    }
    
    void terminate() {

    }
    
    void update(t3::tick_t delta_time) {

    }

    void suspend(t3::tick_t delta_time) {

    }

private:
    t3::SpriteLayer sp_layer_;

};






ZipTestScene::ZipTestScene()
    : Scene("ZipTest") {
    context_.reset(T3_SYS_NEW SceneContext());
}

ZipTestScene::~ZipTestScene() {
    
}


void ZipTestScene::initializeScene() {
    context_->initialize();
}


void ZipTestScene::terminateScene() {
    context_->terminate();
}


void ZipTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void ZipTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















