////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_audio_resource.hpp
    オーディオリソース.
*/

#ifndef TRI_AUDIO_RESOURCE_HPP_INCLUDED
#define TRI_AUDIO_RESOURCE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/base/tri_resource.hpp"
#include "core/base/tri_resource_manager.hpp"
#include "tri_audio_handle.hpp"


TRI_CORE_NS_BEGIN

//  前方宣言
class Wav;

///
/// オーディオリソース
class AudioResource final
    : Resource
{
private:
    /// 
    /// コンストラクタ.
    /// create関数経由でしか生成できない
    AudioResource();

public:
    ///
    /// デストラクタ
    ~AudioResource();

    ///
    /// サウンド生成
    SharedPtr<AudioHandle>  createSound();

public:
    ///
    /// リソースの生成関数.
    static SharedPtr<AudioResource> create(FilePath& filepath);



private:
    ///
    /// バッファ構築
    void setupBuffer(
        const Wav& wav  ///< wavから構築
    );

private:
    cross::AudioSystem::BufferID id_;   ///< バッファID
};


///
/// オーディオリソースマネージャ
using AudioManager = ResourceManager<AudioResource>;



TRI_CORE_NS_END

#endif // TRI_AUDIO_RESOURCE_HPP_INCLUDED
