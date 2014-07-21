#ifndef TRI_AUDIO_HANDLE_HPP_INCLUDED
#define TRI_AUDIO_HANDLE_HPP_INCLUDED

#include "tri_audio_system.hpp"

namespace t3 {
inline namespace audio {

class AudioResource;

class AudioHandle {
    friend class AudioResource;
private:
    explicit AudioHandle(
        AudioSystem::buffer_id_t buffer_id
    );

public:
    ~AudioHandle();

public:
    void playBGM();
    void stopBGM();
    
    void playSE();
    void stopSE();

    void pitch(float speed);
    void volume(float vol);

private:
    
    void play(bool loop = false);

    void stop();
    
private:
    
    AudioSystem::source_id_t sid_;
    bool bgm_;
};



}   // namespace audio
}   // namespace t3

#endif // TRI_AUDIO_HANDLE_HPP_INCLUDED
