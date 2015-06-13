/**
    @file tri_wav.hpp
    ウェブサウンド.
*/
#ifndef TRI_WAV3_HPP_INCLUDED
#define TRI_WAV3_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "kernel/io/tri_filepath.hpp"


TRI_CORE_NS_BEGIN

///
/// ウェブサウンド
class Wav {

public:
    ///
    /// ウェブ情報
    struct Info {
        Info()
            : size_(0)
            , time_(0.0f)
            , channel_(0)
            , bit_per_sample_(0)
            , sampling_rate_(0)
            , data_pos_(0)
        {}
    
        size_t size_;               ///< データサイズ
        float time_;                ///< 再生時間
        short channel_;             ///< チャンネル数
        short bit_per_sample_;      ///< ビットレート
        int sampling_rate_;         ///< サンプリングレート
        std::streamoff data_pos_;   ///< 再生位置
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
    /// ビットレート取得
    int bitPerSample() const {
        return info_.bit_per_sample_;
    }
    
    ///
    /// サンプリングレート取得
    int samplingRate() const {
        return info_.sampling_rate_;
    }

    ///
    /// サイズ取得
    size_t size() const {
        return info_.size_;
    }
    
    ///
    /// データ取得
    const uint8_t* getData() const {
        return data_;
    }

    ///
    /// チャンネル数取得
    int channel() const {
        return info_.channel_;
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
        return info_.time_;
    }
    
    ///
    /// 読み込み終了判定
    bool isReadEnd() {
        return info_.size_ == readed_size_;
    }
    
    ///
    /// ファイルを開く
    void open(const FilePath& filepath);
    
    ///
    /// 読み込み
    size_t read(void* out, size_t size);
    
    ///
    /// ファイルを閉じる
    void close();
    
    ///
    /// 読み込みリセット
    void readReset();


private:
    FileStream file_;       ///< ファイルストリーム
    Info info_;             ///< 情報
    size_t readed_size_;    ///< 読み込み済サイズ
    uint8_t* data_;         ///< データ
};


TRI_CORE_NS_END
#endif // TRI_WAV_HPP_INCLUDED
