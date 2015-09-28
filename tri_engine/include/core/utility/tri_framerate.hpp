////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_framerate.hpp
    フレームレート変換.
*/

#ifndef TRI_FRAMERATE_HPP_INCLUDED
#define TRI_FRAMERATE_HPP_INCLUDED


#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


///
/// フレームレートN時の1フレームあたりの秒数取得
template <int FRAMERATE>
constexpr float frameSec() {
    return 1.0f / FRAMERATE;
}


///
/// フレームを秒に変換
inline float frameToSec(
    int frame   ///< フレーム数
) {
    return static_cast<float>(frame) / 60.0f;
}

///
/// 秒をフレームに変換
inline int secToFrame(
    float sec   ///< 秒
) {
    return static_cast<int>(sec * 60.0f);
}

///
/// デルタタイムあたりのレート
inline float deltaRate(
    float delta_time    ///< 現在のデルタタイム
) {
    return delta_time / frameSec<60>();
}
    
    
TRI_CORE_NS_END

#endif // TRI_FRAMERATE_HPP_INCLUDED

