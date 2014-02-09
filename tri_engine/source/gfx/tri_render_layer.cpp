

#include "tri_render_layer.hpp"
#include <cstring>


namespace t3{
inline namespace gfx {
    

RenderLayer::RenderLayer(
    const char* const name,
    const int priority
)   : pause_(false)
    , visible_(true)
    , priority_(priority)
    , dmf_me_(nullptr, name)
    , dmi_visible_(&dmf_me_, "VISIBLE", visible_, 1)
    , dmi_pause_(&dmf_me_, "PAUSE", pause_, 1)
{
}
    
RenderLayer::RenderLayer(const char* const name)
    : RenderLayer( name, PRIORITY_NORMAL )
{
}



RenderLayer::~RenderLayer()
{

}

void RenderLayer::setPriority( const int priority )
{
    T3_ASSERT( PRIORITY_LOWEST <= priority && priority <= PRIORITY_HIGHEST  );
    priority_ = priority;
}

void RenderLayer::setLayerName( const char* const name )
{
    std::strncpy( layer_name_, name, LAYER_NAME_SIZE );
}


void RenderLayer::registryToDebugMenu(
    DebugMenuFrame& parent
) {
    dmf_me_.attachSelf(parent);
}

void RenderLayer::unregistryToDebugMenu()
{
    dmf_me_.detachSelf();
}
    
    
    
//  レイヤー更新
void updateLayers(
    RenderLayers& layers,
    tick_t tick
){
    for ( auto layer : layers ){
        if (!layer->isPauseLayer()) {
            layer->updateLayer( tick );
        }
    }
}
    
void drawLayers(
    RenderLayers& layers
){
    for ( auto layer : layers ){
        if (layer->isVisibleLayer()) {
            layer->drawLayer();
        }
    }
}
    
    



}   // inline namespace gfx
}   // namespace t3

