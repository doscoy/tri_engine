////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/audio/tri_audio_handle.hpp"


TRI_CORE_NS_BEGIN


///
/// コンストラクタ
AudioHandle::AudioHandle(
    const cross::AudioSystem::BufferID buffer_id
)   : sid_(0)
    , bgm_(false)
    , volume_(1.0f)
    , last_volume_(1.0f)
{
    //  ソースIDを生成
    sid_ = cross::AudioSystem::createSource(buffer_id);
}

///
/// デストラクタ
AudioHandle::~AudioHandle() {
    //  ソースIDを破棄
    cross::AudioSystem::deleteSource(sid_);
}

///
/// 単純再生
void AudioHandle::play(
    bool loop   ///< ループ指定
) {
    //  ループを指定して再生
    cross::AudioSystem::setLoop(sid_, loop);
    cross::AudioSystem::play(sid_);
}

///
/// 停止
void AudioHandle::stop() {
    cross::AudioSystem::stop(sid_);
}

///
/// BGMとして再生
void AudioHandle::playBGM() {
    bgm_ = true;
    play(true);
}

///
/// BGMを静止
void AudioHandle::stopBGM() {
    stop();
}

///
/// SEとして再生
void AudioHandle::playSE() {
    bgm_ = false;
    play();
}

///
/// SEを停止
void AudioHandle::stopSE() {
    stop();
}

///
/// ピッチの設定
void AudioHandle::pitch(
    const float speed
) {
    cross::AudioSystem::pitch(sid_, speed);
}

///
/// ボリュームの設定
void AudioHandle::volume(
    const float vol
) {
    if (muted_) {
        //  ミュート中はボリューム変更せず、ミュートが終了した時に反映されるようにする
        last_volume_ = vol;
    } else {
        //  ミュート中じゃないので通常の音量変更処理
        last_volume_ = volume_;
        volume_ = vol;
        cross::AudioSystem::volume(sid_, vol);
    }
}


TRI_CORE_NS_END

