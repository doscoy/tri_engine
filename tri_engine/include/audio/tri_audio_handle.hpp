#ifndef TRI_AUDIO_HANDLE_HPP_INCLUDED
#define TRI_AUDIO_HANDLE_HPP_INCLUDED

#include "tri_audio_system.hpp"

namespace t3 {
inline namespace audio {

class AudioResource;

class AudioHandle {
    friend class AudioResource;
private:
    AudioHandle();

public:
    ~AudioHandle();

public:
    
    void play();
    
    void stop();
    
private:
    
    AudioSystem::source_id_t sid_;
};



}   // namespace audio
}   // namespace t3

#endif // TRI_AUDIO_HANDLE_HPP_INCLUDED
