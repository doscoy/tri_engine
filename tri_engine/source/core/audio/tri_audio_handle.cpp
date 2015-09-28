////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/audio/tri_audio_handle.hpp"


TRI_CORE_NS_BEGIN



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


TRI_CORE_NS_END

