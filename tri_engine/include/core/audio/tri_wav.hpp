////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_wav.hpp
    ウェブサウンド.
*/
#ifndef TRI_WAV3_HPP_INCLUDED
#define TRI_WAV3_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/kernel/io/tri_filepath.hpp"
#include "core/kernel/io/tri_file.hpp"

TRI_CORE_NS_BEGIN

///
/// ウェブサウンド
class Wav {

public:
    ///
    /// ウェブ情報

    ///
    /// wavのヘッダ構造体
    struct WavFileHeader {
        uint32_t riff_signature_;       // RIFF
        uint32_t size_;                 // Data size (filesize - 8 byte)
        uint32_t wav_signature_;        // WAVE
        uint32_t fmt_signature_;        // fmt
        uint32_t fmt_chunk_byte_size_;  // fmtチャンクのバイト数
        uint16_t format_id_;
        uint16_t channel_;
        uint32_t sampling_rate_;
        uint32_t byte_per_sec_;
        uint16_t block_size_;
        uint16_t bit_per_sample_;
    };

public:
    ///
    /// コンストラクタ
    Wav();
    
    ///
    /// デストラクタ
    ~Wav();

public:
    ///
    /// ロード
    void load(const FilePath& filepath);

    ///
    ///
    void setup(const t3::File& file);
    
    
    ///
    ///
    void setupstream(t3::FileStream& file);
    
    ///
    /// ビットレート取得
    int bitPerSample() const {
        return header_.bit_per_sample_;
    }
    
    ///
    /// サンプリングレート取得
    int samplingRate() const {
        return header_.sampling_rate_;
    }

    ///
    /// サイズ取得
    size_t size() const {
        return size_;
    }
    
    ///
    /// データ取得
    const uint8_t* getData() const {
        return data_;
    }

    ///
    /// チャンネル数取得
    int channel() const {
        return header_.channel_;
    }

    ///
    /// ステレオ判定
    bool isStereo() const {
        return channel() == 2;
    }
    
    ///
    /// モノラル判定
    bool isMonaural() const {
        return channel() == 1;
    }
    
    ///
    /// 再生時間取得
    float time() {
        return playtime_;
    }
    
    ///
    /// 読み込み終了判定
    bool isReadEnd() {
        return size_ == readed_size_;
    }
    
    ///
    /// ファイルを開く
    void openstream(const FilePath& filepath);
    
    ///
    /// 読み込み
    size_t readstream(void* out, size_t size);
    
    ///
    /// ファイルを閉じる
    void closestream();
    
    ///
    /// 読み込みリセット
    void readReset();


private:
    FileStream file_steram_;    ///< ファイルストリーム
    WavFileHeader header_;      ///< wavファイルヘッダ
    size_t size_;
    size_t readed_size_;        ///< 読み込み済サイズ
    uint8_t* data_;             ///< データ
    bool datastrage_allocated_;
    std::streamoff data_pos_;   ///< 再生位置
    float playtime_;
};


TRI_CORE_NS_END
#endif // TRI_WAV_HPP_INCLUDED
