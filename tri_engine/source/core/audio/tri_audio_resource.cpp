////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/audio/tri_audio_resource.hpp"
#include "core/audio/tri_wav.hpp"
#include "core/debug/tri_trace.hpp"
#include "core/debug/tri_assert.hpp"

TRI_CORE_NS_BEGIN


///
/// コンストラクタ
AudioResource::AudioResource()
    : id_()
    , handle_()
{
    //  オーディオのリソース用バッファを割当
    id_ = cross::AudioSystem::createBuffer();
}

///
/// デストラクタ
AudioResource::~AudioResource() {
    //  バッファを削除
    cross::AudioSystem::deleteBuffer(id_);
}


///
/// オーディオリソース生成
AudioResourcePtr AudioResource::create(
    FilePath& filepath  ///< ファイルパス
) {
    //  未サポート判定
    T3_ASSERT_MSG(filepath.ext() == ".wav", "%s is not support. only supported .wav", filepath.filename().c_str());
    
    //  とりあえず.wavだけサポート
    Wav wav;
    wav.load(filepath);
    
    //  リソース生成
    AudioResourcePtr res;
    res.reset(T3_SYS_NEW AudioResource);
    res->setupBuffer(wav);
    res->resourceName(filepath.filename().c_str());
    res->createHandle();
    return res;
}


///
/// オーディオリソース生成
AudioResourcePtr AudioResource::create(
    const t3::File& file    ///< ファイル
) {    
    //  とりあえず.wavだけサポート
    Wav wav;
    wav.setup(file);
    
    //  リソース生成
    AudioResourcePtr res;
    res.reset(T3_SYS_NEW AudioResource);
    res->resourceName(file.name().c_str());
    res->setupBuffer(wav);
    res->createHandle();
    return res;
}


///
/// サウンドファイル生成
void AudioResource::createHandle() {
    
    handle_.reset(
        T3_SYS_NEW AudioHandle(id_)
    );
}

///
/// バッファ構築
void AudioResource::setupBuffer(
    const Wav& wav  ///< 元となるサウンドデータ
) {
    //  オーディオフォーマット調査
    cross::AudioSystem::AudioFormat format;

    if (wav.channel() == 1) {
        // モノラル
        if (wav.bitPerSample() == 8) {
            format = cross::AudioSystem::AudioFormat::MONO_8;
        }
        else {
            format = cross::AudioSystem::AudioFormat::MONO_16;
        }
    }
    else {
        // ステレオ
        if (wav.bitPerSample() == 8) {
            format = cross::AudioSystem::AudioFormat::STEREO_8;
        }
        else {
            format = cross::AudioSystem::AudioFormat::STEREO_16;
        }
    }
    
    //  バッファ生成
    cross::AudioSystem::setBufferData(
        id_,
        format,
        wav.getData(),
        wav.size(),
        wav.samplingRate()
    );
 
    //  生成ログ出力
    T3_SYSTEM_LOG("create Wav\n");
    T3_SYSTEM_LOG(" channel %d\n", wav.channel());
    T3_SYSTEM_LOG(" bit sample %d\n", wav.bitPerSample());
    T3_SYSTEM_LOG(" rate %d\n", wav.samplingRate());
    T3_SYSTEM_LOG(" size %d\n", wav.size());

}


TRI_CORE_NS_END

