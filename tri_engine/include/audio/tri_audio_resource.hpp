#ifndef TRI_AUDIO_RESOURCE_HPP_INCLUDED
#define TRI_AUDIO_RESOURCE_HPP_INCLUDED

#include "base/tri_resource.hpp"
#include "base/tri_resource_manager.hpp"
#include "tri_audio_system.hpp"
#include "tri_audio_handle.hpp"


namespace t3 {
inline namespace audio {

class Wav;

class AudioResource final
    : Resource
{
private:
    AudioResource();

public:
    ~AudioResource();

    std::shared_ptr<AudioHandle>  createSound();

public:
    static std::shared_ptr<AudioResource> create(FilePath& filepath);



private:
    void setupBuffer(const Wav& wav);

private:
    AudioSystem::BufferID id_;
};


using AudioManager = ResourceManager<AudioResource>;


} // namespace auido
} // namespace t3

#endif // TRI_AUDIO_RESOURCE_HPP_INCLUDED
