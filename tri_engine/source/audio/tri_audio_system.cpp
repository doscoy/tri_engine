

#include "audio/tri_audio_system.hpp"
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


AudioSystem::BufferID AudioSystem::createBuffer() {
    BufferID id;
    alGenBuffers(1, &id);
    return id;
}

void AudioSystem::deleteBuffer(
    AudioSystem::BufferID id
) {
    alDeleteBuffers(1, &id);
}


AudioSystem::SourceID AudioSystem::createSource(BufferID buffer) {
    SourceID source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    return source;
}

void AudioSystem::deleteSource(SourceID source) {
    alDeleteSources(1, &source);
}


void AudioSystem::play(AudioSystem::SourceID sid) {
    alSourcePlay(sid);
}


void AudioSystem::stop(AudioSystem::SourceID sid) {
    alSourceStop(sid);
}

void AudioSystem::setLoop(
    SourceID sid,
    bool loop
) {
    alSourcei(sid, AL_LOOPING, loop);
}

void AudioSystem::setBufferData(
    const BufferID id,
    const AudioSystem::AudioFormat format,
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

void AudioSystem::pitch(
    const SourceID sid,
    const float speed
) {
    T3_ASSERT_RANGE(speed, 0.0f, 1.0f);
    alSourcef(sid, AL_PITCH, speed);
}

void AudioSystem::volume(
    const SourceID sid,
    const float vol
) {
    T3_ASSERT_RANGE(vol, 0.0f, 1.0f);
    alSourcef(sid, AL_GAIN, vol);
}



}   // namespace audio
}   // namepsace t3