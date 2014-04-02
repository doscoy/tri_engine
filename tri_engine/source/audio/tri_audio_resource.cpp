


#include "audio/tri_audio_resource.hpp"


namespace t3 {
inline namespace audio {

AudioResource::AudioResource()
    : id_()
{
    id_ = AudioSystem::generateBuffer();
}

AudioResource::~AudioResource() {
    AudioSystem::deleteBuffer(id_);
}


std::shared_ptr<AudioResource> AudioResource::create(
    FilePath& filepath
) {
    std::shared_ptr<AudioResource> res;
    res.reset(new AudioResource);
    return res;
}


std::shared_ptr<AudioHandle> AudioResource::createSound() {
    
    std::shared_ptr<AudioHandle> audio_handle;
    audio_handle.reset(
        new AudioHandle
    );
    
    return audio_handle;
}



}   // namespace audio
}   // namepsace t3