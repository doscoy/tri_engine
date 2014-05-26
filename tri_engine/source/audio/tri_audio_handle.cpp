

#include "tri_audio_handle.hpp"


namespace t3 {
inline namespace audio {

AudioHandle::AudioHandle(
    const AudioSystem::buffer_id_t buffer_id
)   : sid_(0)
    , bgm_(false)
{
    sid_ = AudioSystem::generateSource(buffer_id);
}

AudioHandle::~AudioHandle() {
    AudioSystem::deleteSource(sid_);
}


void AudioHandle::play(bool loop) {
    AudioSystem::setLoop(sid_, loop);
    AudioSystem::play(sid_);
}

void AudioHandle::stop() {
    AudioSystem::stop(sid_);
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



}   // namespace audio
}   // namepsace t3