////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_audio_system.hpp
    オーディオ制御API.
*/

#ifndef CROSS_AUDIO_SYSTEM_HPP_INCLUDED
#define CROSS_AUDIO_SYSTEM_HPP_INCLUDED

//  include
#include "cross_buildlevel.hpp"
#include "cross_config.hpp"
#include <cstdlib>
#include <cstdint>

CROSS_NS_BEGIN

///
/// オーディオシステム
class AudioSystem {
public:
    ///
    /// システムの初期化
    static void initializeAudioSystem();

    ///
    /// システムの後片付け
    static void terminateAudioSystem();

    ///
    /// バッファID
    using BufferID = unsigned int;

    ///
    /// ソースID
    using SourceID = unsigned int;
    
    ///
    /// オーディオフォーマット
    enum class AudioFormat {
        MONO_8,     ///< モノラル8bit
        MONO_16,    ///< モノラル16bit
        STEREO_8,   ///< ステレオ8bit
        STEREO_16   ///< ステレオ16bit
    };
    
    ///
    /// フォーマットを返す
    static AudioFormat format(
    	int channel,    ///< チャンネル数
    	int bps         ///< bit/sec
    ) {
    	AudioFormat format;
	    if (channel == 1) {
    	    // モノラル
        	if (bps == 8) {
       	     	format = AudioSystem::AudioFormat::MONO_8;
        	}
        	else {
            	format = AudioSystem::AudioFormat::MONO_16;
        	}
    	}
    	else {
        	// ステレオ
        	if (bps == 8) {
            	format = AudioSystem::AudioFormat::STEREO_8;
        	}
        	else {
            	format = AudioSystem::AudioFormat::STEREO_16;
        	}
    	}
    
    	return format;
    }
    
    ///
    /// バッファデータ設定
    static void setBufferData(
        const BufferID id,
        const AudioFormat format,
        const uint8_t* data,
        const size_t size,
        const int sampling_rate
    );
    
    ///
    /// バッファ生成
    static BufferID createBuffer();
    
    ///
    /// バッファ削除
    static void deleteBuffer(BufferID buffer);

    ///
    /// バッファからソース作成
    static SourceID createSource();
    
    ///
    /// バッファからソース作成
    static SourceID createSource(
        BufferID buffer
    );
    
    ///
    /// ソースを削除
    static void deleteSource(SourceID source);


    ///
    /// バッファをキューにためる
    static void queueBuffers(
        const SourceID source,
        size_t size,
        const BufferID* buffer
    );
    
    ///
    /// バッファをキューから除去
    static void unqueueBuffers(
        const SourceID source,
        size_t size,
        BufferID* buffer
    );
    
    
    ///
    /// 更新
    static int getSourceProcessed(
        const AudioSystem::SourceID source
    );

    
    ///
    /// 再生
    static void play(SourceID sid);
    
    ///
    /// 停止
    static void stop(SourceID sid);
    
    
    ///
    /// ループ指定
    static void setLoop(SourceID sid, bool loop);
    
    ///
    /// ピッチ調整
    static void pitch(const SourceID sid, const float speed);
    
    ///
    /// ボリューム調整
    static void volume(const SourceID sid, const float vol);
};




CROSS_NS_END

#endif // CROSS_AUDIO_SYSTEM_HPP_INCLUDED
