

#include "audio/tri_wav.hpp"
#include "kernel/memory/tri_memory.hpp"



namespace {
    
    
int readHeaderWav(
    FILE* fp,
    int* channel,
    int* bit,
    size_t* size,
    int* freq
){

    short res16;
    int res32;
    int data_size, chunk_size;
    short channel_count,bit_par_sample,block_size;
    int sampling_rate,byte_par_sec;
    
    long dataPos = 0;
    int flag = 0;
    
    fread(&res32, 4, 1,fp);
    if(res32 != 0x46464952){	//"RIFF"
        return 1;	//error 1
    }
    
    //データサイズ = ファイルサイズ - 8 byte の取得
    fread(&data_size, 4, 1, fp);
    
    //WAVEヘッダーの読み
    fread(&res32, 4, 1, fp);
    if(res32 != 0x45564157){	//"WAVE"
        return 2;	//error 2
    }
    
    while(flag != 3){
        //チャンクの読み
        fread(&res32, 4, 1, fp);
        fread(&chunk_size, 4, 1, fp);
        
        switch(res32){
            case 0x20746d66:	//"fmt "
                //format 読み込み
                //PCM種類の取得
                fread(&res16, 2, 1, fp);
                if(res16 != 1){
                    //非対応フォーマット
                    return 4;
                }
                //モノラル(1)orステレオ(2)
                fread(&channel_count, 2, 1, fp);
                if(res16 > 2){
                    //チャンネル数間違い
                    return 5;
                }
                //サンプリングレート
                fread(&sampling_rate, 4, 1, fp);
                //データ速度(byte/sec)=サンプリングレート*ブロックサイズ
                fread(&byte_par_sec, 4, 1, fp);
                //ブロックサイズ(byte/sample)=チャンネル数*サンプルあたりのバイト数
                fread(&block_size, 2, 1, fp);
                //サンプルあたりのbit数(bit/sample)：8 or 16
                fread(&bit_par_sample, 2, 1, fp);
                
                *channel = (int)channel_count;
                *bit = (int)bit_par_sample;
                *freq = sampling_rate;
                
                flag += 1;
                
                break;
            case  0x61746164:	//"data"
                
                *size = chunk_size;
                
                dataPos = ftell(fp);
                
                flag += 2;
                break;
        }
        
    }
    
    //頭出し("fmt "が"data"より後にあった場合のみ動く)
    if (dataPos != ftell(fp)){
        fseek(fp,dataPos,SEEK_SET);
    }
    
    return 0;
}
    
    
}   // unname namespace


namespace t3 {
inline namespace audio {

Wav::Wav()
{}


Wav::~Wav()
{
    
}

void Wav::load(FilePath& filepath ) {
    FILE* fp = fopen(filepath.getFullPath().c_str(), "rb");
    readHeaderWav(fp, &channel_, &bit_per_sample_, &size_, &sampling_rate_);
    
    data_ = T3_ALLOC(size_);
    fread(data_, size_, 1, fp);

    fclose(fp);
}




}   // namespace audio
}   // namepsace t3
