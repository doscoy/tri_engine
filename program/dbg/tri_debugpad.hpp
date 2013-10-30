#ifndef TRI_DEBUGPAD_HPP_INCLUDED
#define TRI_DEBUGPAD_HPP_INCLUDED

#include "../io/tri_pad.hpp"

namespace t3 {
inline namespace dbg {

    
const Pad& debugPad();
void updateDebugPad( const uint32_t pad_data, tick_t tick );
    
}   // inline namespace dbg
}   // namespace t3





#endif // TRI_DEBUGPAD_HPP_INCLUDED