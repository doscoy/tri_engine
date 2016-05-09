////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/base/tri_frame_info.hpp"
#include "core/utility/tri_framerate.hpp"


TRI_CORE_NS_BEGIN

void FrameInfo::deltaTime(float dt) {
    delta_time_ = dt;
    delta_rate_ = dt / (frameSec<60>());
}


TRI_CORE_NS_END

