#include "dbg/tri_debugpad.hpp"

namespace  {

t3::Pad debug_pad_;
    
}   // unname namespace

namespace t3 {


const Pad& debugPad(){
    return debug_pad_;
}
    
void updateDebugPad( const cross::GamePadData& pad_data, tick_t delta_time )
{
    debug_pad_.updatePad( pad_data, delta_time );
}

}   // namespace t3