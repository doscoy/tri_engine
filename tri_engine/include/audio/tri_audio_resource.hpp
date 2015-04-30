#ifndef TRI_AUDIO_RESOURCE_HPP_INCLUDED
#define TRI_AUDIO_RESOURCE_HPP_INCLUDED

#include "base/tri_resource.hpp"
#include "base/tri_resource_manager.hpp"
#include "tri_audio_handle.hpp"


namespace t3 {

class Wav;

class AudioResource final
    : Resource
{
private:
    AudioResource();

public:
    ~AudioResource();

    SharedPtr<AudioHandle>  createSound();

public:
    static SharedPtr<AudioResource> create(FilePath& filepath);



private:
    void setupBuffer(const Wav& wav);

private:
    cross::AudioSystem::BufferID id_;
};


using AudioManager = ResourceManager<AudioResource>;



} // namespace t3

#endif // TRI_AUDIO_RESOURCE_HPP_INCLUDED
