


#include "core/audio/tri_audio_resource.hpp"
#include "core/audio/tri_wav.hpp"
#include "core/debug/tri_trace.hpp"
#include "core/debug/tri_assert.hpp"

TRI_CORE_NS_BEGIN



AudioResource::AudioResource()
    : id_()
{
    id_ = cross::AudioSystem::createBuffer();
}

AudioResource::~AudioResource() {
    cross::AudioSystem::deleteBuffer(id_);
}


SharedPtr<AudioResource> AudioResource::create(
    FilePath& filepath
) {
    if (filepath.ext() != ".wav") {
        T3_PANIC("%s is not found.\n", filepath.fullpath().c_str());
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
    cross::AudioSystem::AudioFormat format;

    if (wav.channel() == 1) {
        // モノラル
        if (wav.bitPerSample() == 8) {
            format = cross::AudioSystem::AudioFormat::MONO_8;
        }
        else {
            format = cross::AudioSystem::AudioFormat::MONO_16;
        }
    }
    else {
        // ステレオ
        if (wav.bitPerSample() == 8) {
            format = cross::AudioSystem::AudioFormat::STEREO_8;
        }
        else {
            format = cross::AudioSystem::AudioFormat::STEREO_16;
        }
    }
    
    cross::AudioSystem::setBufferData(
        id_,
        format,
        wav.getData(),
        wav.size(),
        wav.samplingRate()
    );
 
    T3_SYSTEM_LOG("create Wav\n");
    T3_SYSTEM_LOG(" channel %d\n", wav.channel());
    T3_SYSTEM_LOG(" bit sample %d\n", wav.bitPerSample());
    T3_SYSTEM_LOG(" rate %d\n", wav.samplingRate());
    T3_SYSTEM_LOG(" size %d\n", wav.size());

}


TRI_CORE_NS_END
