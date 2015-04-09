#ifndef TRI_AUDIO_HANDLE_HPP_INCLUDED
#define TRI_AUDIO_HANDLE_HPP_INCLUDED

#include <cross_sdk/cross_sdk.hpp>

namespace t3 {
inline namespace audio {

class AudioResource;

class AudioHandle {
    friend class AudioResource;
private:
    explicit AudioHandle(
        cross::AudioSystem::BufferID buffer_id
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
    
    cross::AudioSystem::SourceID sid_;
    bool bgm_;
};



}   // namespace audio
}   // namespace t3

#endif // TRI_AUDIO_HANDLE_HPP_INCLUDED
