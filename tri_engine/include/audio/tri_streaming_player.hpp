#ifndef TRI_STREAMING_PLAYER_HPP_INCLUDED
#define TRI_STREAMING_PLAYER_HPP_INCLUDED

#include "tri_wav.hpp"
#include "cross_sdk.hpp"
#include <array>



namespace t3 {


class StreamingPlayer {
    enum {
        BUFFER_SIZE = 3,
    };
    
public:
    StreamingPlayer();
    ~StreamingPlayer();


public:
    void initialize(const FilePath& path, int read_byte);
    void poling();
    
    void play(bool loop = true) {
        loop_ = loop;
        cross::AudioSystem::play(source_id_);
    }

    void stop() {
        cross::AudioSystem::stop(source_id_);
    }

    
private:
    void readMore();
    void processBuffer(cross::AudioSystem::BufferID id);
    cross::AudioSystem::BufferID createBuffer();
    void switchCurrentBuffer();
    void switchReadingBuffer();
    
    size_t currentBufferSize() const {
        return buffer_[current_buffer_index_].size_;
    }
    
    uint8_t* currentBufferStorage() const {
        return buffer_[current_buffer_index_].storage_;
    }
    
    uint8_t* readingBufferStorage() const {
        return buffer_[reading_buffer_index_].storage_;
    }
    
    
private:
    t3::Wav wav_;
    int read_byte_;
    
    
    int reading_buffer_index_;
    int current_buffer_index_;
    cross::AudioSystem::SourceID source_id_;

    Array<cross::AudioSystem::BufferID, BUFFER_SIZE> buffer_id_;

    struct BufferStorage {
        BufferStorage()
            : storage_(nullptr)
            , size_(0)
        {
        }
        
        uint8_t* storage_;
        size_t size_;
    };
    Array<BufferStorage, BUFFER_SIZE> buffer_;;

    bool loop_;
};


}   // t3




#endif  // TRI_STRAMING_PLAYER_HPP_INCLUDED
