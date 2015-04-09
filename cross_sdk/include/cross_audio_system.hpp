#ifndef CROSS_AUDIO_SYSTEM_HPP_INCLUDED
#define CROSS_AUDIO_SYSTEM_HPP_INCLUDED


#include <cstdlib>
#include <cstdint>

namespace cross {


class AudioSystem {
public:
    static void initializeAudioSystem();
    static void terminateAudioSystem();


    using BufferID = unsigned int;
    using SourceID = unsigned int;
    
    enum class AudioFormat {
        MONO_8,
        MONO_16,
        STEREO_8,
        STEREO_16
    };
    static AudioFormat format(
    	int channel,
    	int bps
    ) {
    	AudioFormat format;
	    if (channel == 1) {
    	    // モノラル
        	if (bps == 8) {
       	     	format = AudioSystem::AudioFormat::MONO_8;
        	}
        	else {
            	format = AudioSystem::AudioFormat::MONO_16;
        	}
    	}
    	else {
        	// ステレオ
        	if (bps == 8) {
            	format = AudioSystem::AudioFormat::STEREO_8;
        	}
        	else {
            	format = AudioSystem::AudioFormat::STEREO_16;
        	}
    	}
    
    	return format;
    }
    
    
    
    static void setBufferData(
        const BufferID id,
        const AudioFormat format,
        const uint8_t* data,
        const size_t size,
        const int sampling_rate
    );
    static BufferID createBuffer();
    static void deleteBuffer(BufferID buffer);

    static SourceID createSource();
    static SourceID createSource(
        BufferID buffer
    );
    static void deleteSource(SourceID source);


    static void queueBuffers(
        const SourceID source,
        size_t size,
        const BufferID* buffer
    );
    
    static void unqueueBuffers(
        const SourceID source,
        size_t size,
        BufferID* buffer
    );
    
    
    static int getSourceProcessed(
        const AudioSystem::SourceID source
    );

    
    static void play(SourceID sid);
    static void stop(SourceID sid);
    
    static void setLoop(SourceID sid, bool loop);
    static void pitch(const SourceID sid, const float speed);
    static void volume(const SourceID sid, const float vol);
};




}   // namespace cross

#endif // CROSS_AUDIO_SYSTEM_HPP_INCLUDED
