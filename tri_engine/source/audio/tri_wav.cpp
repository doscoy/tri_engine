

#include "audio/tri_wav.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "dbg/tri_dbg.hpp"
#include "util/tri_util.hpp"

namespace {
    
    
int readWaveHeader(
    std::ifstream& file,
    t3::Wav::Info& info
) {

/*
    std::streamoff top = file.tellg();

    for (int i = 0; i < 20000; ++i) {
        uint32_t das;
        file.read((char*)&das, 4);
    
        if (das == t3::makeSignature('R', 'I', 'F', 'F')) {
            T3_TRACE("RIFF\n");
        }
        else if (das == t3::makeSignature('W', 'A', 'V', 'E')) {
            T3_TRACE("WAVE\n");
        }
        else if (das == t3::makeSignature('f', 'm', 't', ' ')) {
            T3_TRACE("fmt\n");
        }
        else if (das == t3::makeSignature('d', 'a', 't', 'a')) {
            T3_TRACE("data\n");
        }
        else if (das == t3::makeSignature('D', 'A', 'T', 'A')) {
            T3_TRACE("DATA\n");
        }
    }


    file.seekg(top);
*/
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
    
    //  データの先頭の取得
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



   /*
    int flag = 0;
    
    int res32;
    fread(&res32, 4, 1,fp);
    if(res32 != 0x46464952){	//"RIFF"
        return 1;	//error 1
    }
    
    //データサイズ = ファイルサイズ - 8 byte の取得
    fread(&info.size_, 4, 1, fp);
    
    //WAVEヘッダーの読み
    fread(&res32, 4, 1, fp);
    if(res32 != 0x45564157){	//"WAVE"
        return 2;	//error 2
    }
    
    while(flag != 3){
        //チャンクの読み
        fread(&res32, 4, 1, fp);
        int chunk_size;
        fread(&chunk_size, 4, 1, fp);
        
        switch(res32){
            case 0x20746d66:	//"fmt "
                //format 読み込み
                //PCM種類の取得
                short res16;
                fread(&res16, 2, 1, fp);
                if(res16 != 1){
                    //非対応フォーマット
                    return 4;
                }
                //モノラル(1)orステレオ(2)
                fread(&info.channel_, 2, 1, fp);
                if(res16 > 2){
                    //チャンネル数間違い
                    return 5;
                }
                //サンプリングレート
                int byte_par_sec;
                fread(&info.sampling_rate_, 4, 1, fp);
                
                //データ速度(byte/sec)=サンプリングレート*ブロックサイズ
                fread(&byte_par_sec, 4, 1, fp);
                
                //ブロックサイズ(byte/sample)=チャンネル数*サンプルあたりのバイト数
                short block_size;
                fread(&block_size, 2, 1, fp);
                
                //サンプルあたりのbit数(bit/sample)：8 or 16
                fread(&info.bit_per_sample_, 2, 1, fp);
                
                
                flag += 1;
                
                break;
            case  0x61746164:	//"data"
                
                info.size_ = chunk_size;
                
                info.data_pos_ = ftell(fp);
                
                flag += 2;
                break;
        }
        
    }
    
    
    
    
    //頭出し("fmt "が"data"より後にあった場合のみ動く)
    if (info.data_pos_ != ftell(fp)){
        fseek(fp, info.data_pos_, SEEK_SET);
    }
    
    info.time_ = info.size_ / info.channel_ / 2.0f / info.sampling_rate_;

    return 0;
    */
}
    
    
}   // unname namespace


namespace t3 {
inline namespace audio {

Wav::Wav()
    : file_(nullptr)
    , info_()
    , readed_size_(0)
    , data_(nullptr)
{}


Wav::~Wav() {
    file_.close();
    T3_FREE(data_);
}

void Wav::load(const FilePath& filepath ) {
    open(filepath);
    
    data_ = (uint8_t*)T3_SYS_ALLOC(info_.size_);
    read(data_, info_.size_);
    
    close();
}

void Wav::open(const t3::FilePath &filepath) {

    file_.open(filepath.getFullPath().c_str(), std::ios::binary);
    readWaveHeader(file_, info_);
}

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
    file_.read((char*)out, size);
    
    //  トータル読み込みサイズ更新
    readed_size_ += read_size;
    return read_size;
}


void Wav::close() {
    file_.close();
}

void Wav::readReset() {
    readed_size_ = 0;
    file_.clear();
    file_.seekg(info_.data_pos_);
}



}   // namespace audio
}   // namepsace t3
