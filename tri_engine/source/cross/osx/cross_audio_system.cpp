////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "cross_audio_system.hpp"

CROSS_NS_BEGIN




void AudioSystem::initializeAudioSystem() {

}



void AudioSystem::terminateAudioSystem() {
    
}


AudioSystem::BufferID AudioSystem::createBuffer() {
    return 0;
}

void AudioSystem::deleteBuffer(
    AudioSystem::BufferID id
) {

}


AudioSystem::SourceID AudioSystem::createSource() {


    return 0;
}


AudioSystem::SourceID AudioSystem::createSource(BufferID buffer) {

    return 0;
}

void AudioSystem::deleteSource(SourceID source) {

}


void AudioSystem::queueBuffers(
    const SourceID source,
    size_t size,
    const BufferID* buffer
) {

}

void AudioSystem::unqueueBuffers(
    const SourceID source,
    size_t size,
    BufferID* buffer
) {

}


void AudioSystem::play(AudioSystem::SourceID sid) {

}


void AudioSystem::stop(AudioSystem::SourceID sid) {

}

void AudioSystem::setLoop(
    SourceID sid,
    bool loop
) {

}

void AudioSystem::setBufferData(
    const BufferID id,
    const AudioSystem::AudioFormat format,
    const uint8_t *data,
    const std::size_t size,
    const int sampling_rate
) {
}

void AudioSystem::pitch(
    const SourceID sid,
    const float speed
) {

}

void AudioSystem::volume(
    const SourceID sid,
    const float vol
) {

}


int AudioSystem::getSourceProcessed(
    const AudioSystem::SourceID source
) {

    return 0;
}


CROSS_NS_END
