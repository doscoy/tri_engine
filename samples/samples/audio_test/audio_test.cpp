

#include "audio_test.hpp"
#include <vector>




class AudioTestScene::SceneContext {

public:
    SceneContext()
        : res_(nullptr)
        , handle_(nullptr)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize(){
        t3::FilePath wav_path("sample.wav");
        res_ = t3::AudioResource::create(wav_path);
        handle_ = res_->createSound();
    }
    
    void terminate(){

    }
    
    void update(t3::tick_t delta_time){
        const t3::Input& input = t3::GameSystem::getInstance().getInput();
        const t3::Pointing& ptng = input.getPointing();
        
        if (ptng.isRelease()) {
            handle_->playSE();
        }
    }

    void suspend(t3::tick_t delta_time) {

    }

    
private:


private:
    std::shared_ptr<t3::AudioResource> res_;
    std::shared_ptr<t3::AudioHandle> handle_;
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
        setFinish(true);
    }
}

void AudioTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}
















