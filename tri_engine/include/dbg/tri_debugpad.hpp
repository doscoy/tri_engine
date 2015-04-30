#ifndef TRI_DEBUGPAD_HPP_INCLUDED
#define TRI_DEBUGPAD_HPP_INCLUDED

#include "../kernel/tri_kernel.hpp"

namespace t3 {


    
const Pad& debugPad();
void updateDebugPad( const uint32_t pad_data, tick_t delta_time );

}   // namespace t3





#endif // TRI_DEBUGPAD_HPP_INCLUDED