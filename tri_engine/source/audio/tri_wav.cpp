

#include "audio/tri_wav.hpp"
#include "kernel/memory/tri_memory.hpp"
#include "dbg/tri_assert.hpp"


namespace {
    
    
int readWaveHeader(
    FILE* fp,
    t3::Wav::Info& info
) {
    
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
    if (file_) {
        close();
    }
}

void Wav::load(const FilePath& filepath ) {
    open(filepath);
    
    // 再生時間(秒)
    data_ = (uint8_t*)T3_ALLOC(info_.size_);
    read(data_, info_.size_);
    
    close();
}

void Wav::open(const t3::FilePath &filepath) {
    T3_ASSERT(!file_);
    file_ = fopen(filepath.getFullPath().c_str(), "rb");
    readWaveHeader(file_, info_);
}

size_t Wav::read(void* out, size_t size) {
    T3_ASSERT(file_);
    size_t read_size = size;
    if (readed_size_ + size > info_.size_) {
        read_size = info_.size_ - readed_size_;
    }
    fread(out, read_size, 1, file_);
    readed_size_ += read_size;
    return read_size;
}


void Wav::close() {
    fclose(file_);
    file_ = nullptr;
}

void Wav::readReset() {
    readed_size_ = 0;
    fseek(file_, info_.data_pos_, SEEK_SET);
}



}   // namespace audio
}   // namepsace t3
