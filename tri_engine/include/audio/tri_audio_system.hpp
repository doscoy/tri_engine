#ifndef TRI_AUDIO_SYSTEM_HPP_INCLUDED
#define TRI_AUDIO_SYSTEM_HPP_INCLUDED



#include "kernel/io/tri_filepath.hpp"




namespace t3 {
inline namespace audio {

class AudioSystem {
public:
    static void initializeAudioSystem();
    static void terminateAudioSystem();


    using BufferID = unsigned int;
    using source_id_t = unsigned int;
    
    enum class AudioFormat {
        MONO_8,
        MONO_16,
        STEREO_8,
        STEREO_16
    };
    
    static void setBufferData(
        const BufferID id,
        const AudioFormat format,
        const uint8_t* data,
        const size_t size,
        const int sampling_rate
    );
    static BufferID generateBuffer();
    static void deleteBuffer(BufferID buffer);

    static source_id_t generateSource(
        BufferID buffer
    );
    static void deleteSource(source_id_t source);

    static void play(source_id_t sid);
    static void stop(source_id_t sid);
    
    static void setLoop(source_id_t sid, bool loop);
    static void pitch(const source_id_t sid, const float speed);
    static void volume(const source_id_t sid, const float vol);
};




}   // namespace audio
}   // namespace t3

#endif // TRI_AUDIO_SYSTEM_HPP_INCLUDED
