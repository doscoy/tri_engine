////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_streaming_player.hpp
    ストリーミングサウンドプレイヤー.
*/

#ifndef TRI_STREAMING_PLAYER_HPP_INCLUDED
#define TRI_STREAMING_PLAYER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "cross/cross.hpp"
#include "tri_wav.hpp"
#include <array>


TRI_CORE_NS_BEGIN


///
/// ストリーミングサウンドプレイヤー
class StreamingPlayer {
    enum {
        BUFFER_SIZE = 3,    ///< バッファの数
    };
    
public:
    ///
    /// コンストラクタ
    StreamingPlayer();
    
    ///
    /// デストラクタ
    ~StreamingPlayer();


public:
    ///
    /// 初期化
    void initialize(const FilePath& path, int read_byte);
    
    ///
    /// ポーリング
    void poling();
    
    ///
    /// 再生
    void play(bool loop = true) {
        loop_ = loop;
        cross::AudioSystem::play(source_id_);
    }

    ///
    /// 停止
    void stop() {
        cross::AudioSystem::stop(source_id_);
    }

    
private:
    ///
    /// 続きを読み込み
    void readMore();
    
    ///
    /// バッファを処理する
    void processBuffer(cross::AudioSystem::BufferID id);
    
    ///
    /// バッファ生成
    cross::AudioSystem::BufferID createBuffer();
    
    ///
    /// カレントバッファを切り替え
    void switchCurrentBuffer();
    
    ///
    /// 読み込みバッファを切り替え
    void switchReadingBuffer();
    
    ///
    /// カレントバッファのサイズ
    size_t currentBufferSize() const {
        return buffer_[current_buffer_index_].size_;
    }
    
    ///
    /// カレントバッファのストレージを取得
    uint8_t* currentBufferStorage() const {
        return buffer_[current_buffer_index_].storage_;
    }
    
    ///
    /// 読み込みバッファのストレージを取得
    uint8_t* readingBufferStorage() const {
        return buffer_[reading_buffer_index_].storage_;
    }
    
    
private:
    t3::Wav wav_;   ///< wavサウンド
    int read_byte_; ///< 読み込みバイトサイズ
    
    
    int reading_buffer_index_;  ///< 裏読み中のバッファ番号
    int current_buffer_index_;  ///< 再生中のバッファ番号
    cross::AudioSystem::SourceID source_id_;    ///< ソースID

    Array<cross::AudioSystem::BufferID, BUFFER_SIZE> buffer_id_;    ///< バッファID

    ///
    /// バッファストレージ
    struct BufferStorage {
        BufferStorage()
            : storage_(nullptr)
            , size_(0)
        {}
        
        uint8_t* storage_;  ///< ストレージ
        size_t size_;       ///< サイズ
    };
    Array<BufferStorage, BUFFER_SIZE> buffer_;  ///< バッファコンテナ

    bool loop_; ///< ループフラグ
};


TRI_CORE_NS_END




#endif  // TRI_STRAMING_PLAYER_HPP_INCLUDED
