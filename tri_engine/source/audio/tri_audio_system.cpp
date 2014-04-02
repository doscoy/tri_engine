

#include "tri_audio_system.hpp"
#include "platform/platform_sdk.hpp"
#include "dbg/tri_assert.hpp"



namespace t3 {
inline namespace audio {

namespace {

ALCdevice* device_ = nullptr;
ALCcontext* context_ = nullptr;


}   // unname namespace



void AudioSystem::initializeAudioSystem() {
    device_ = alcOpenDevice(nullptr);
    T3_NULL_ASSERT(device_);
    
    context_ = alcCreateContext(device_, nullptr);
    T3_NULL_ASSERT(context_);
}



void AudioSystem::terminateAudioSystem() {
    
}


AudioSystem::buffer_id_t AudioSystem::generateBuffer() {
    buffer_id_t id;
    alGenBuffers(1, &id);
    return id;
}

void AudioSystem::deleteBuffer(
    AudioSystem::buffer_id_t id
) {
    alDeleteBuffers(1, &id);
}


AudioSystem::source_id_t AudioSystem::generateSource(buffer_id_t buffer) {
    source_id_t source;
    alGenSources(1, &source);


    return source;
}

void AudioSystem::deleteSource(source_id_t source) {
    alDeleteSources(1, &source);
}


void AudioSystem::play(AudioSystem::source_id_t sid) {
    alSourcePlay(sid);
}


void AudioSystem::stop(AudioSystem::source_id_t sid) {
    alSourceStop(sid);
}




}   // namespace audio
}   // namepsace t3