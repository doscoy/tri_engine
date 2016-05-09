////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_frame_info.hpp
    型定義.
*/

#ifndef TRI_FRAME_INFO_HPP_INCLUDED
#define TRI_FRAME_INFO_HPP_INCLUDED

#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


class FrameInfo {
public:
    ///
    /// デルタ時間設定
    void deltaTime(float dt);

    ///
    /// デルタ時間取得
    float deltaTime() const {
        return delta_time_;
    }

    ///
    /// デルタレート
    float deltaRate() const {
        return delta_rate_;
    }



private:
    float delta_time_;
    float frame_sec_;
    float delta_rate_;
};


TRI_CORE_NS_END

#endif // TRI_FRAME_INFO_HPP_INCLUDED