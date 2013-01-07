#include "tri_debugpad.hpp"

namespace  {

t3::Pad debug_pad_;
    
}   // unname namespace

namespace t3 {
inline namespace dbg {

const Pad& debugPad(){
    return debug_pad_;
}
    
void updateDebugPad( const u_int pad_data )
{
    debug_pad_.updatePad( pad_data );
}

}   // inline namespace dbg
}   // namespace t3