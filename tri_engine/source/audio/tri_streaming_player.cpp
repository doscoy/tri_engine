
#include "tri_streaming_player.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "platform/platform_sdk.hpp"

namespace t3 {
inline namespace audio {

StreamingPlayer::StreamingPlayer()
    : wav_()
    , read_byte_(0)
{

}


StreamingPlayer::~StreamingPlayer() {
    wav_.close();
}


void StreamingPlayer::initialize(
    const t3::FilePath& path,
    const int read_byte
) {
    //  一回でバッファリングするバイト数
    read_byte_ = read_byte;
    
    
    //  バッファリング領域確保
    buffer_[0] = T3_ALLOC(read_byte);
    buffer_[1] = T3_ALLOC(read_byte);
    
    //  ０版バッファを使用
    current_buffer_ = 0;
    
    //  wav一部読み込み
    wav_.open(path);
    wav_.read(buffer_[0], read_byte);
    
    
}


void StreamingPlayer::poling() {

    int processed;
    alGetSourcei(source_id_, AL_BUFFERS_PROCESSED, &processed);

    if (processed) {
        // 処理を終えたキューをデキュー
        ALuint buffer;
        
        alSourceUnqueueBuffers( source_id_, 1, &buffer );
        // バッファを埋める
//        buffer = wav.CreateBuffer( bufferSize, buffer );
        // エンキュー
        alSourceQueueBuffers( source_id_, 1, &buffer );
    }

}



}   // namespace audio
}   // namespace t3
