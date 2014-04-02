

#include "ad_test.hpp"



class AdScene::SceneContext {

public:
    SceneContext()
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){

    }
    
    void terminate(){

    }
    
    void update(t3::tick_t delta_time){


    }

    void suspend(t3::tick_t delta_time) {

    }

    
private:


private:

};






AdScene::AdScene()
    : Scene( "AudioTest" ) {
    context_.reset(T3_NEW SceneContext());
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
    
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getInput().getPad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish_ = true;
    }
}

void AdScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















