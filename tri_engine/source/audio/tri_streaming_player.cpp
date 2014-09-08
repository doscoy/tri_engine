
#include "tri_streaming_player.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "platform/platform_sdk.hpp"
#include "dbg/tri_trace.hpp"


namespace t3 {
inline namespace audio {

StreamingPlayer::StreamingPlayer()
    : wav_()
    , read_byte_(0)
    , buffer_{nullptr , nullptr}
    , next_buffer_(0)
    , source_id_(0)
    , current_buffer_(0)
{
    alGenSources(1, &source_id_);
}


StreamingPlayer::~StreamingPlayer() {
    stop();
    wav_.close();
    AudioSystem::deleteSource(source_id_);
    
    for (auto& buffer_id : buffer_id_) {
        AudioSystem::deleteBuffer(buffer_id);
    }

}


void StreamingPlayer::initialize(
    const t3::FilePath& path,
    const int read_byte
) {
    //  一回でバッファリングするバイト数
    read_byte_ = read_byte;
    
    
    //  バッファリング領域確保
    buffer_[0] = (uint8_t*)T3_ALLOC(read_byte);
    buffer_[1] = (uint8_t*)T3_ALLOC(read_byte);
    
    //  wav一部読み込み
    wav_.open(path);
    buffer_id_[0] = createBuffer();
    buffer_id_[1] = createBuffer();
    
    
    alSourceQueueBuffers(source_id_, buffer_id_.size(), &buffer_id_[0]);
}

size_t StreamingPlayer::readMore() {
    size_t read = wav_.read(buffer_[next_buffer_], read_byte_);
    current_buffer_ = next_buffer_;
    next_buffer_ = next_buffer_ ? 0 : 1;
    return read;
}

AudioSystem::BufferID StreamingPlayer::createBuffer() {
    AudioSystem::BufferID id = AudioSystem::createBuffer();
    processBuffer(id);
    return id;
}

void StreamingPlayer::poling() {

    int processed;
    alGetSourcei(source_id_, AL_BUFFERS_PROCESSED, &processed);

    if (processed) {
        AudioSystem::BufferID buffer;

        // 処理を終えたキューをデキュー
        alSourceUnqueueBuffers(source_id_, 1, &buffer);

        // バッファを埋める
        processBuffer(buffer);
        
        // エンキュー
        alSourceQueueBuffers(source_id_, 1, &buffer);
        T3_TRACE("Queue Streaming.\n");
    }

}

void StreamingPlayer::processBuffer(AudioSystem::BufferID id) {
    size_t read_size = readMore();
    AudioSystem::setBufferData(
        id,
        AudioSystem::format(wav_.channel(), wav_.bitPerSample()),
        buffer_[current_buffer_],
        read_size,
        wav_.samplingRate()
    );
}



}   // namespace audio
}   // namespace t3
