

#include "ui_button_test.hpp"



class UiButtonScene::SceneContext {

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
        
    }

    void suspend(t3::tick_t delta_time) {

    }

    
private:
    bool show_ad_;
};






UiButtonScene::UiButtonScene()
    : Scene( "AudioTest" ) {
    context_.reset(T3_NEW SceneContext());
}

UiButtonScene::~UiButtonScene() {
    
}


void UiButtonScene::initializeScene() {
    context_->initialize();
}


void UiButtonScene::terminateScene() {
    context_->terminate();
}


void UiButtonScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish(true);
    }
}

void UiButtonScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















