

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


        t3::FilePath stream_path("streaming.wav");
        stream_res_ = t3::AudioResource::create(stream_path);
        stream_handle_ = stream_res_->createSound();

    }
    
    void terminate(){

    }
    
    void update(t3::tick_t delta_time){
        const t3::Input& input = t3::Director::instance().input();
        const t3::Pointing& ptng = input.pointing();
        
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


    std::shared_ptr<t3::AudioResource> stream_res_;
    std::shared_ptr<t3::AudioHandle> stream_handle_;

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
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void AudioTestScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}















