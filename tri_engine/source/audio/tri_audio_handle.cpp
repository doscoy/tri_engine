

#include "tri_audio_handle.hpp"


namespace t3 {
inline namespace audio {

AudioHandle::AudioHandle(
    const AudioSystem::buffer_id_t buffer_id
)   : sid_(0)
{
    sid_ = AudioSystem::generateSource(buffer_id);
}

AudioHandle::~AudioHandle() {
    AudioSystem::deleteSource(sid_);
}


void AudioHandle::play() {
    AudioSystem::play(sid_);
}

void AudioHandle::stop() {
    AudioSystem::stop(sid_);
}



}   // namespace audio
}   // namepsace t3