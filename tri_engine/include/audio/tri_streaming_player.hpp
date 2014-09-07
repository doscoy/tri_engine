#ifndef TRI_STREAMING_PLAYER_HPP_INCLUDED
#define TRI_STREAMING_PLAYER_HPP_INCLUDED

#include "tri_wav.hpp"
#include "tri_audio_system.hpp"

namespace t3 {
inline namespace audio {

class StreamingPlayer {

public:
    StreamingPlayer();
    ~StreamingPlayer();


public:
    void initialize(const FilePath& path, int read_byte);
    void poling();
    
private:


private:
    t3::Wav wav_;
    int read_byte_;
    void* buffer_[2];
    int current_buffer_;
    AudioSystem::SourceID source_id_;
};



}   // audio
}   // t3






#endif  // TRI_STRAMING_PLAYER_HPP_INCLUDED
