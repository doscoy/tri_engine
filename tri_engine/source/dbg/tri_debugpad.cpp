#include "dbg/tri_debugpad.hpp"

namespace  {

t3::Pad debug_pad_;
    
}   // unname namespace

namespace t3 {
inline namespace dbg {

const Pad& debugPad(){
    return debug_pad_;
}
    
void updateDebugPad( const uint32_t pad_data, tick_t delta_time )
{
    debug_pad_.updatePad( pad_data, delta_time );
}

}   // inline namespace dbg
}   // namespace t3