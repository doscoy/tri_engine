
#include "tri_debug_string_layer.hpp"

namespace t3 {
inline namespace dbg {
 

DebugStringLayer::DebugStringLayer(const char* const name)
    : RenderLayer(name, RenderLayer::PRIORITY_DEBUG)
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
    const rgba32_t color,
    const char *const str
){
    debug_string_buffer_.addString( x, y, color, str );
}

void DebugStringLayer::drawLayer()
{
    //  デバッグフォント描画用の設定
    ogl::depthFunc(GL_ALWAYS);
    ogl::disable(GL_LIGHTING);
    
    //  描画
    debug_string_buffer_.drawStrings();
    debug_string_buffer_.clearBuffer();
}


}   // inline namespace dbg
}   // namespace t3