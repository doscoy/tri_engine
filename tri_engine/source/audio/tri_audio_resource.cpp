


#include "audio/tri_audio_resource.hpp"
#include "audio/tri_wav.hpp"

namespace t3 {
inline namespace audio {

AudioResource::AudioResource()
    : id_()
{
    id_ = AudioSystem::createBuffer();
}

AudioResource::~AudioResource() {
    AudioSystem::deleteBuffer(id_);
}


SharedPtr<AudioResource> AudioResource::create(
    FilePath& filepath
) {
    if (filepath.ext() != ".wav") {
        T3_PANIC("%s is not found.\n", filepath.getFullPath().c_str());
    }
    
    Wav wav;
    wav.load(filepath);
    
    SharedPtr<AudioResource> res;
    res.reset(T3_SYS_NEW AudioResource);
    res->setupBuffer(wav);
    return res;
}


SharedPtr<AudioHandle> AudioResource::createSound() {
    
    SharedPtr<AudioHandle> audio_handle;
    audio_handle.reset(
        T3_SYS_NEW AudioHandle(id_)
    );
    
    return audio_handle;
}

void AudioResource::setupBuffer(
    const Wav& wav
) {
    AudioSystem::AudioFormat format;

    if (wav.channel() == 1) {
        // モノラル
        if (wav.bitPerSample() == 8) {
            format = AudioSystem::AudioFormat::MONO_8;
        }
        else {
            format = AudioSystem::AudioFormat::MONO_16;
        }
    }
    else {
        // ステレオ
        if (wav.bitPerSample() == 8) {
            format = AudioSystem::AudioFormat::STEREO_8;
        }
        else {
            format = AudioSystem::AudioFormat::STEREO_16;
        }
    }
    
    AudioSystem::setBufferData(
        id_,
        format,
        wav.getData(),
        wav.size(),
        wav.samplingRate()
    );
 
    T3_TRACE("create Wav\n");
    T3_TRACE(" channel %d\n", wav.channel());
    T3_TRACE(" bit sample %d\n", wav.bitPerSample());
    T3_TRACE(" rate %d\n", wav.samplingRate());
    T3_TRACE(" size %d\n", wav.size());

}

}   // namespace audio
}   // namepsace t3