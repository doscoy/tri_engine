


#include "audio/tri_audio_resource.hpp"
#include "audio/tri_wav.hpp"

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
    if (filepath.getExt() != ".wav") {
        T3_PANIC("%s is not found.\n", filepath.getFullPath().c_str());
    }
    
    Wav wav;
    wav.load(filepath);
    
    std::shared_ptr<AudioResource> res;
    res.reset(new AudioResource);
    res->setupBuffer(wav);
    return res;
}


std::shared_ptr<AudioHandle> AudioResource::createSound() {
    
    std::shared_ptr<AudioHandle> audio_handle;
    audio_handle.reset(
        new AudioHandle(id_)
    );
    
    return audio_handle;
}

void AudioResource::setupBuffer(
    const Wav& wav
) {
    AudioSystem::AudioFormat format;

    if (wav.getChannel() == 1) {
        // モノラル
        if (wav.getBitPerSamle() == 8) {
            format = AudioSystem::AudioFormat::MONO_8;
        }
        else {
            format = AudioSystem::AudioFormat::MONO_16;
        }
    }
    else {
        // ステレオ
        if (wav.getBitPerSamle() == 8) {
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
        wav.getDataSize(),
        wav.getSamplingRate()
    );
 
    T3_TRACE("create Wav\n");
    T3_TRACE(" channel %d\n", wav.getChannel());
    T3_TRACE(" bit sample %d\n", wav.getBitPerSamle());
    T3_TRACE(" rate %d\n", wav.getSamplingRate());
    T3_TRACE(" size %d\n", wav.getDataSize());

}

}   // namespace audio
}   // namepsace t3