#include "debug/tri_debugpad.hpp"

TRI_CORE_NS_BEGIN


namespace  {

t3::Pad debug_pad_;
    
}   // unname namespace




const Pad& debugPad(){
    return debug_pad_;
}
    
void updateDebugPad( const cross::GamePadData& pad_data, tick_t delta_time )
{
    debug_pad_.updatePad( pad_data, delta_time );
}

TRI_CORE_NS_END