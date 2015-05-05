
#include "dbg/tri_debug_string_layer.hpp"




namespace t3 {

 

DebugStringLayer::DebugStringLayer(const char* const name)
    : RenderLayer(name, RenderLayer::PRIORITY_DEBUG)
{

}

DebugStringLayer::~DebugStringLayer()
{
    
}

void DebugStringLayer::updateLayer( tick_t delta_time )
{
    
}

void DebugStringLayer::writeString(
    const float x,
    const float y,
    const rgba32_t color,
    const int size,
    const char *const str
){
    debug_string_buffer_.addString(x, y, color, size, str);
}

void DebugStringLayer::drawLayer()
{
    //  デバッグフォント描画用の設定
    cross::RenderSystem::setDepthTestMode(cross::RenderSystem::DepthTestMode::MODE_ALWAYS);
    
    //  描画
    debug_string_buffer_.drawStrings();
    debug_string_buffer_.clearBuffer();
}


}   // namespace t3
