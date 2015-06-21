

#include "ad_test.hpp"



class AdScene::SceneContext {

public:
    SceneContext()
        : show_ad_(false)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){

    }
    
    void terminate(){

    }
    
    void update(t3::tick_t delta_time){
        const t3::Input& input = t3::Director::instance().input();
        const t3::Pointing& ptng = input.pointing();
        
        if (ptng.isRelease()) {
            if (show_ad_) {
                show_ad_ = false;
//                t3::cross::hideAd();
            }
            else {
                show_ad_ = true;
//                t3::cross::showAd();
            }
        }
    }

    void suspend(t3::tick_t delta_time) {

    }

    
private:
    bool show_ad_;
};






AdScene::AdScene()
    : SceneBase( "AudioTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

AdScene::~AdScene() {
    
}


void AdScene::initializeScene() {
    context_->initialize();
}


void AdScene::terminateScene() {
    context_->terminate();
}


void AdScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void AdScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















