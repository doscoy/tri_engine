
#include "tri_debug_screen_layer.hpp"

namespace t3 {
inline namespace dbg {
 

DebugScreenLayer::DebugScreenLayer()
    : RenderLayer( "DEBUG SCREEN", RenderLayer::PRIORITY_DEBUG )
{

}

DebugScreenLayer::~DebugScreenLayer()
{
    
}

void DebugScreenLayer::updateLayer( tick_t tick )
{
    
}

void DebugScreenLayer::writeString(
    const int x,
    const int y,
    const u_int color,
    const char *const str
){
    debug_string_buffer_.addString( x, y, color, str );
}

void DebugScreenLayer::drawLayer()
{
    debug_string_buffer_.drawStrings();
    debug_string_buffer_.clearBuffer();
}


}   // inline namespace dbg
}   // namespace t3