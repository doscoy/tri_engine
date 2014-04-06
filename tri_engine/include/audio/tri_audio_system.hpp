#ifndef TRI_AUDIO_SYSTEM_HPP_INCLUDED
#define TRI_AUDIO_SYSTEM_HPP_INCLUDED



#include "kernel/io/tri_filepath.hpp"




namespace t3 {
inline namespace audio {

class AudioSystem {
public:
    static void initializeAudioSystem();
    static void terminateAudioSystem();


    using buffer_id_t = unsigned int;
    using source_id_t = unsigned int;
    
    enum class AudioFormat {
        MONO_8,
        MONO_16,
        STEREO_8,
        STEREO_16
    };
    
    static void setBufferData(
        const buffer_id_t id,
        const AudioFormat format,
        const uint8_t* data,
        const size_t size,
        const int sampling_rate
    );
    static buffer_id_t generateBuffer();
    static void deleteBuffer(buffer_id_t buffer);

    static source_id_t generateSource(
        buffer_id_t buffer
    );
    static void deleteSource(source_id_t source);

    static void play(source_id_t sid);
    static void stop(source_id_t sid);

};




}   // namespace audio
}   // namespace t3

#endif // TRI_AUDIO_SYSTEM_HPP_INCLUDED
