

#include "audio/tri_audio_handle.hpp"


namespace t3 {


AudioHandle::AudioHandle(
    const cross::AudioSystem::BufferID buffer_id
)   : sid_(0)
    , bgm_(false)
{
    sid_ = cross::AudioSystem::createSource(buffer_id);
}

AudioHandle::~AudioHandle() {
    cross::AudioSystem::deleteSource(sid_);
}


void AudioHandle::play(bool loop) {
    cross::AudioSystem::setLoop(sid_, loop);
    cross::AudioSystem::play(sid_);
}

void AudioHandle::stop() {
    cross::AudioSystem::stop(sid_);
}

void AudioHandle::playBGM() {
    bgm_ = true;
    play(true);
}

void AudioHandle::stopBGM() {
    stop();
}

void AudioHandle::playSE() {
    bgm_ = false;
    play();
}

void AudioHandle::stopSE() {
    stop();
}

void AudioHandle::pitch(
    const float speed
) {
    cross::AudioSystem::pitch(sid_, speed);
}

void AudioHandle::volume(
    const float vol
) {
    cross::AudioSystem::volume(sid_, vol);
}


}   // namepsace t3

