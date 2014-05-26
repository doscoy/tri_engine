

#include "tri_audio_system.hpp"
#include "platform/platform_sdk.hpp"
#include "dbg/tri_assert.hpp"
#include "dbg/tri_trace.hpp"


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
    
    alcMakeContextCurrent(context_);
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
    alSourcei(source, AL_BUFFER, buffer);

    return source;
}

void AudioSystem::deleteSource(source_id_t source) {
    alDeleteSources(1, &source);
}


void AudioSystem::play(AudioSystem::source_id_t sid) {
    T3_TRACE("alSoundPlay %d\n", sid);
    alSourcePlay(sid);
}


void AudioSystem::stop(AudioSystem::source_id_t sid) {
    T3_TRACE("alSoundStop %d\n", sid);
    alSourceStop(sid);
}

void AudioSystem::setLoop(
    source_id_t sid,
    bool loop
) {
    alSourcei(sid, AL_LOOPING, loop);
}

void AudioSystem::setBufferData(
    const buffer_id_t id,
    const t3::AudioSystem::AudioFormat format,
    const uint8_t *data,
    const size_t size,
    const int sampling_rate
) {
    ALenum al_format = AL_FORMAT_MONO8;

    switch (format) {
        case AudioFormat::MONO_8:
            al_format = AL_FORMAT_MONO8;
            break;

        case AudioFormat::MONO_16:
            al_format = AL_FORMAT_MONO16;
            break;

        case AudioFormat::STEREO_8:
            al_format = AL_FORMAT_STEREO8;
            break;

        case AudioFormat::STEREO_16:
            al_format = AL_FORMAT_STEREO16;
            break;
        default:
            break;
    }
    alBufferData(id, al_format, data, (ALsizei)size, sampling_rate);
}


}   // namespace audio
}   // namepsace t3