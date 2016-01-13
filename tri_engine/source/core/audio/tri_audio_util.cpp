////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/audio/tri_audio_handle.hpp"
#include "core/audio/tri_audio_resource.hpp"

TRI_CORE_NS_BEGIN

bool playSE(
    const String& name
) {
    auto& audio_man = AudioManager::instance();
    auto& res = audio_man.findResource(name);
    if (!res) {
        //  指定のサウンドは存在しない
        return false;
    }
    
    res->handle()->playSE();
    return true;
}


bool playBGM(
    const String& name
) {
    auto& audio_man = AudioManager::instance();
    auto& res = audio_man.findResource(name);
    if (!res) {
        //  指定のサウンドは存在しない
        return false;
    }
    
    res->handle()->playBGM();
    return true;
}

bool stopSE(
    const String& name
) {
    auto& audio_man = AudioManager::instance();
    auto& res = audio_man.findResource(name);
    if (!res) {
        //  指定のサウンドは存在しない
        return false;
    }
    
    res->handle()->stopSE();
    return true;
}

bool stopBGM(
    const String& name
) {
    auto& audio_man = AudioManager::instance();
    auto& res = audio_man.findResource(name);
    if (!res) {
        //  指定のサウンドは存在しない
        return false;
    }
    
    res->handle()->stopBGM();
    return true;
}


bool changeVolume(
    const String& name,
    float vol
) {
    auto& audio_man = AudioManager::instance();
    auto& res = audio_man.findResource(name);
    if (!res) {
        //  指定のサウンドは存在しない
        return false;
    }
    
    res->handle()->volume(vol);
    return true;
}


void muteAllSound(bool flag) {


    auto& audio_man = AudioManager::instance();
    auto& resources = audio_man.resources();


    for (auto& audio_res: resources) {
        audio_res->handle()->mute(flag);
    }
}


TRI_CORE_NS_END