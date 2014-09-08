#ifndef TRI_STREAMING_PLAYER_HPP_INCLUDED
#define TRI_STREAMING_PLAYER_HPP_INCLUDED

#include "tri_wav.hpp"
#include "tri_audio_system.hpp"
#include <array>



namespace t3 {
inline namespace audio {

class StreamingPlayer {

public:
    StreamingPlayer();
    ~StreamingPlayer();


public:
    void initialize(const FilePath& path, int read_byte);
    void poling();
    
    void play() {
        AudioSystem::play(source_id_);
    }

    void stop() {
        AudioSystem::stop(source_id_);
    }

    
private:
    size_t readMore();
    void processBuffer(AudioSystem::BufferID id);
    AudioSystem::BufferID createBuffer();
    
private:
    t3::Wav wav_;
    int read_byte_;
    uint8_t* buffer_[2];
    int next_buffer_;
    int current_buffer_;
    AudioSystem::SourceID source_id_;
    std::array<AudioSystem::BufferID, 2> buffer_id_;
};



}   // audio
}   // t3






#endif  // TRI_STRAMING_PLAYER_HPP_INCLUDED
