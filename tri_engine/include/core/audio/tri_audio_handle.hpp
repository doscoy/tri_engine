////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_audio_handle.hpp
    オーディオ操作のためのハンドルクラス.
*/

#ifndef TRI_AUDIO_HANDLE_HPP_INCLUDED
#define TRI_AUDIO_HANDLE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "cross/cross_sdk.hpp"


TRI_CORE_NS_BEGIN

//  前方宣言
class AudioResource;

///
/// オーディオ操作のためのハンドルクラス
class AudioHandle {
    friend class AudioResource;
private:
    ///
    /// コンストラクタ.
    /// オーディオリソースからしか生成できなくするためprivate
    explicit AudioHandle(
        cross::AudioSystem::BufferID buffer_id
    );

public:
    ///
    /// デストラクタ
    ~AudioHandle();

public:
    ///
    /// BGMとして再生
    void playBGM();

    ///
    /// BGMとして停止
    void stopBGM();
    
    ///
    /// SEとして再生
    void playSE();

    ///
    /// SEとして停止
    void stopSE();

    ///
    /// ピッチ設定
    void pitch(float speed);

    ///
    /// ボリューム設定
    void volume(float vol);

    ///
    /// BGMか判定
    bool isBGM() const {
        return bgm_;
    }

private:
    
    ///
    /// 再生処理.
    void play(bool loop = false);

    ///
    /// 停止処理.
    void stop();
    
private:
    
    cross::AudioSystem::SourceID sid_;  ///< ソースID
    bool bgm_;  ///< BGM判定用フラグ
};



TRI_CORE_NS_END

#endif // TRI_AUDIO_HANDLE_HPP_INCLUDED
