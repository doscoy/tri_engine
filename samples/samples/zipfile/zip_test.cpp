////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "zip_test.hpp"


class ZipTestScene::SceneContext {


public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {
        t3::FilePath path("test.zip");
        t3::ZipFile zip;
        bool init_res = zip.initialize(path.fullpath());
        
        if (!init_res) {
            return;
        }
        
        //  初期化成功
        for (int i = 0; i < zip.entries(); ++i) {
            t3::traceTerminal("%d>%s %d\n",
                i,
                zip.getFileName(i).c_str(),
                zip.getFileSize(i)
            );
        }
        
        
        const size_t buf_size = 99999;
        uint8_t buf[buf_size];
        t3::String hog("hoj/stamp.png");
        zip.readFile(hog, buf);
        t3::File png("hoj/stamp.png", buf_size, buf);
        
        t3::TexturePtr tex = t3::TextureFactory::createFromPngFile(png);
        spr_ = sp_layer_.createSprite(tex);
    
        
    }
    
    void terminate() {

    }
    
    void update(t3::DeltaTime delta_time) {
    }


private:
    t3::SpriteLayer sp_layer_;
    t3::SpritePtr spr_;
};






ZipTestScene::ZipTestScene()
    : SceneBase("ZipTest") {
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


void ZipTestScene::updateScene(t3::DeltaTime delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

















