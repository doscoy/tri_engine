////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "audio_test.hpp"





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


        t3::FilePath stream_path("akb48.wav");
        int buffering_size = 1024 * 100;
        stream_.initialize(stream_path, buffering_size);
        stream_.play();
    }
    
    void terminate(){

    }
    
    void update(t3::DeltaTime delta_time){
        const t3::Input& input = t3::Director::instance().input();
        const t3::Pointing& ptng = input.pointing();
        stream_.poling();
        if (ptng.isRelease()) {
            handle_->playSE();
        }
    }

    
private:


private:
    t3::SharedPtr<t3::AudioResource> res_;
    t3::SharedPtr<t3::AudioHandle> handle_;


    t3::StreamingPlayer stream_;

};






AudioTestScene::AudioTestScene()
    : SceneBase( "AudioTest" ) {
    context_.reset(T3_SYS_NEW SceneContext());
}

AudioTestScene::~AudioTestScene() {
    
}


void AudioTestScene::initializeScene() {
    context_->initialize();
}


void AudioTestScene::terminateScene() {
    context_->terminate();
}


void AudioTestScene::updateScene(t3::DeltaTime delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}
















