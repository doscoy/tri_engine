

#include "audio_test.hpp"
#include <vector>




class AudioTestScene::SceneContext {

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






AudioTestScene::AudioTestScene()
    : Scene( "AudioTest" ) {
    context_.reset(T3_NEW SceneContext());
}

AudioTestScene::~AudioTestScene() {
    
}


void AudioTestScene::initializeScene() {
    context_->initialize();
}


void AudioTestScene::terminateScene() {
    context_->terminate();
}


void AudioTestScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getInput().getPad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish_ = true;
    }
}

void AudioTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















