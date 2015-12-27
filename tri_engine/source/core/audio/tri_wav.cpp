////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "core/audio/tri_wav.hpp"
#include "core/kernel/memory/tri_memory.hpp"
#include "core/debug/tri_dbg.hpp"
#include "core/utility/tri_util.hpp"

namespace {



void* setupWavFromMemory(
    void* data,
    t3::
    
) {
    header_ = ()*data
    return nullptr;
}



///
/// wavのヘッダを読む
int readWaveHeader(
    t3::FileStream& file,
    t3::Wav::Info& info
) {

    // "RIFF" の読み込み
    unsigned int riff;
    file.read((char*)&riff,4);
    T3_ASSERT(riff == t3::makeSignature('R', 'I', 'F', 'F'));
    
    // データサイズを取得
    // データサイズ = ファイルサイズ - 8 byte
    file.read((char*)&info.size_, 4);

    // "WAVE" の読み込み
    uint32_t wave;
    file.read((char*)&wave, 4);
    T3_ASSERT(wave == t3::makeSignature('W', 'A', 'V', 'E'));

    uint32_t fmt;
    file.read((char*)&fmt, 4);
    T3_ASSERT(fmt == t3::makeSignature('f', 'm', 't', ' '));

    //  fmtチャンクのバイト数
    uint32_t chunk_byte;
    file.read((char*)&chunk_byte, 4);

    // PCM 情報の取得
    uint16_t format_id;
    file.read((char*)&format_id,2);
    if (format_id != 1){
        //  非対応フォーマット
        //  リニアPCMじゃない
        return false;
    }
            
    // モノラル(1), ステレオ(2)
    file.read((char*)&info.channel_, 2);
    if (info.channel_ > 2) {
        //  ２チャンネル以上は非対応
        return false;
    }
            
    // サンプリングレート
    file.read((char*)&info.sampling_rate_, 4);
            
    //  データ速度
    //  1秒あたりのバイト数(byte/sec)
    int byte_per_sec;
    file.read((char*)&byte_per_sec, 4);

    // ブロックサイズ(byte/sample)
    int block_size;
    file.read((char*)&block_size, 2);
            
    // サンプルあたりのビット数(bit/sample)
    file.read((char*)&info.bit_per_sample_, 2);
    
    //  データの先頭を探す "data"からデータが始まる
    for(int i = 0; i < 200; ++i){
        uint8_t c;
        file.read((char*)&c, 1);
        
        if (c == 'd') {
            file.read((char*)&c, 1);
            if (c == 'a') {
                file.read((char*)&c, 1);
                if (c == 't') {
                    file.read((char*)&c, 1);
                    if (c == 'a') {
                        //  データサイズ
                        uint32_t size;
                        file.read((char*)&size, 4);
            
                        // データの開始位置を保存
                        info.data_pos_ = file.tellg();
                        info.size_ = size;
                        break;
                    }
                }
            }
        }
    }
    // データの開始位置までシーク
    T3_ASSERT(info.data_pos_);
    file.seekg( info.data_pos_ );

    return true;

}
    
    
}   // unname namespace


TRI_CORE_NS_BEGIN


///
/// コンストラクタ
Wav::Wav()
    : file_steram_()
    , info_()
    , readed_size_(0)
    , data_(nullptr)
{}

///
/// デストラクタ
Wav::~Wav() {
    file_steram_.close();
    T3_FREE(data_);
}

///
/// .wav を読み込む
void Wav::load(
    const FilePath& filepath
) {
    //  ファイルを開いてサイズを取得
    open(filepath);
    
    //  サイズ分のメモリを確保
    data_ = (uint8_t*)T3_SYS_ALLOC(info_.size_);

    //  読み込み
    read(data_, info_.size_);
    
    //  ファイルを閉じる
    close();
}


///
/// .wavのファイルからデータ作成
void Wav::setup(
    const File& file
) {
    
}


///
/// ファイルをひらく
void Wav::open(const t3::FilePath &filepath) {

    file_steram_.open(filepath.fullpath().c_str(), std::ios::binary);
    readWaveHeader(file_steram_, info_);
}

///
/// 読み込み
size_t Wav::read(void* out, size_t size) {

    size_t read_size = size;
    
    //  読み込み予定サイズがデータサイズを超えないよう調整
    if (readed_size_ + size > info_.size_) {
        read_size = info_.size_ - readed_size_;
    }
    
    if (read_size <= 0) {
        return 0;
    }
    
    //  指定サイズを読み込む
    file_steram_.read((char*)out, size);
    
    //  トータル読み込みサイズ更新
    readed_size_ += read_size;
    return read_size;
}


///
/// ファイルを閉じる
void Wav::close() {
    file_steram_.close();
}

///
/// 読み込み情報をリセット
void Wav::readReset() {
    readed_size_ = 0;
    file_steram_.clear();
    file_steram_.seekg(info_.data_pos_);
}


TRI_CORE_NS_END
