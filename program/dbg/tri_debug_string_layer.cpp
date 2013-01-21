
#include "tri_debug_string_layer.hpp"

namespace t3 {
inline namespace dbg {
 

DebugStringLayer::DebugStringLayer()
    : RenderLayer( "DEBUG SCREEN", RenderLayer::PRIORITY_DEBUG )
{

}

DebugStringLayer::~DebugStringLayer()
{
    
}

void DebugStringLayer::updateLayer( tick_t tick )
{
    
}

void DebugStringLayer::writeString(
    const int x,
    const int y,
    const u_int color,
    const char *const str
){
    debug_string_buffer_.addString( x, y, color, str );
}

void DebugStringLayer::drawLayer()
{
    debug_string_buffer_.drawStrings();
    debug_string_buffer_.clearBuffer();
}


}   // inline namespace dbg
}   // namespace t3