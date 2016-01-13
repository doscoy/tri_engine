////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_wav.hpp
    サウンド再生ユーティリティ.
*/
#ifndef TRI_AUDIO_UTIL_HPP_INCLUDED
#define TRI_AUDIO_UTIL_HPP_INCLUDED

//  include
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN

bool playSE(const String& name);
bool playBGM(const String& name);

bool stopSE(const String& name);
bool stopBGM(const String& name);

bool changeVolume(const String& name, float vol);

void muteAllSound(bool flag);

TRI_CORE_NS_END

#endif // TRI_AUDIO_UTIL_HPP_INCLUDED
