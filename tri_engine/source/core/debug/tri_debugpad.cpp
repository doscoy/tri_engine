////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/debug/tri_debugpad.hpp"

TRI_CORE_NS_BEGIN


namespace  {

t3::Pad debug_pad_;
    
}   // unname namespace




const Pad& debugPad(){
    return debug_pad_;
}
    
void updateDebugPad( 
    const cross::GamePadData& pad_data, 
    const FrameInfo& frame_info 
) {
    debug_pad_.updatePad( pad_data, frame_info );
}

TRI_CORE_NS_END