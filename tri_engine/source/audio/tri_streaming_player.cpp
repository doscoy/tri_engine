
#include "tri_streaming_player.hpp"
#include "kernel/memory/tri_memory.hpp"

#include "dbg/tri_trace.hpp"


namespace t3 {
inline namespace audio {


StreamingPlayer::StreamingPlayer()
    : wav_()
    , read_byte_(0)
    , buffer_()
    , reading_buffer_index_(0)
    , current_buffer_index_(0)
    , source_id_(0)
    , buffer_id_()
    , loop_(false)
{
    source_id_ = cross::AudioSystem::createSource();
}


StreamingPlayer::~StreamingPlayer() {
    stop();
    wav_.close();
    cross::AudioSystem::deleteSource(source_id_);
    
    
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cross::AudioSystem::deleteBuffer(buffer_id_[i]);
        T3_FREE(buffer_[i].storage_);
    }


}


void StreamingPlayer::initialize(
    const t3::FilePath& path,
    const int read_byte
) {
    //  一回でバッファリングするバイト数
    read_byte_ = read_byte;
    
    
    //  バッファリング領域確保
    for (int i = 0; i < BUFFER_SIZE; ++i) {

        buffer_[i].storage_ = (uint8_t*)T3_SYS_ALLOC(read_byte);
        buffer_id_[i] = createBuffer();
    }
    
    //  wav 一部読み込み
    wav_.open(path);
    
    cross::AudioSystem::queueBuffers(
        source_id_,
        buffer_id_.size(),
        &buffer_id_[0]
    );

    readMore();
}

//  追加読み込み
void StreamingPlayer::readMore() {

    //  読み込み
    size_t read_size = wav_.read(readingBufferStorage(), read_byte_);
    T3_TRACE("Streaming read %d  buf %d.\n", read_size, reading_buffer_index_);
    
    if (read_size < read_byte_) {
        //  wavの終端まで読んだ
        if (loop_) {
            //  ループなら先頭に戻って続きを読む
            wav_.readReset();
            wav_.read(buffer_[reading_buffer_index_].storage_ + read_size, read_byte_ - read_size);
            read_size = read_byte_;
        }
    }
    
    //  読み込み済サイズ設定
    buffer_[reading_buffer_index_].size_ = read_size;
    
    //  読み込みバッファインデックス更新
    switchReadingBuffer();
}

cross::AudioSystem::BufferID StreamingPlayer::createBuffer() {
    cross::AudioSystem::BufferID id = cross::AudioSystem::createBuffer();
    processBuffer(id);
    return id;
}

void StreamingPlayer::poling() {

    int processed = cross::AudioSystem::getSourceProcessed(source_id_);

    if (processed) {
        cross::AudioSystem::BufferID buffer;

        // 処理を終えたキューをデキュー
        cross::AudioSystem::unqueueBuffers(source_id_, 1, &buffer);

        // バッファを埋める
        processBuffer(buffer);
        
        // エンキュー
        cross::AudioSystem::queueBuffers(source_id_, 1, &buffer);
    }

}

void StreamingPlayer::processBuffer(
    const cross::AudioSystem::BufferID id
) {
    readMore();
    switchCurrentBuffer();

    if (currentBufferSize() == 0) {
        //  もう読み込みバッファが無い
        return;
    }
    
    cross::AudioSystem::setBufferData(
        id,
        cross::AudioSystem::format(wav_.channel(), wav_.bitPerSample()),
        currentBufferStorage(),
        currentBufferSize(),
        wav_.samplingRate()
    );
}


void StreamingPlayer::switchCurrentBuffer() {
    current_buffer_index_ = (current_buffer_index_ + 1) % BUFFER_SIZE;
}

void StreamingPlayer::switchReadingBuffer() {
    reading_buffer_index_ = (reading_buffer_index_ + 1) % BUFFER_SIZE;
}


}   // namespace audio
}   // namespace t3
