
#include "tri_debug_string_layer.hpp"
#include "gfx/tri_render_system.hpp"



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
    const int size,
    const char *const str
){
    debug_string_buffer_.addString(x, y, color, size, str);
}

void DebugStringLayer::drawLayer()
{
    //  デバッグフォント描画用の設定
    t3::RenderSystem::setDepthTestMode(t3::RenderSystem::DepthTestMode::MODE_ALWAYS);
    t3::RenderSystem::setLighting(false);
    
    //  描画
    debug_string_buffer_.drawStrings();
    debug_string_buffer_.clearBuffer();
}


}   // inline namespace dbg
}   // namespace t3