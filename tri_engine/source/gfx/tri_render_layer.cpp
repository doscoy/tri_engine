

#include "tri_render_layer.hpp"
#include "base/tri_director.hpp"
#include <cstring>


namespace t3{
inline namespace gfx {
    

RenderLayer::RenderLayer(
    const std::string& layer_name,
    const int priority
)   : Nameable()
    , pause_(false)
    , visible_(true)
    , priority_(priority)
    , dmf_me_(nullptr, layer_name)
    , dmi_visible_(&dmf_me_, "VISIBLE", visible_, 1)
    , dmi_pause_(&dmf_me_, "PAUSE", pause_, 1)
{
    name(layer_name);
    attachSystem();
}
    
RenderLayer::RenderLayer(const std::string& name)
    : RenderLayer(name, PRIORITY_APP_NORMAL)
{
}



RenderLayer::~RenderLayer()
{
    detachSystem();
}

void RenderLayer::priority(
    const int priority
) {
    T3_ASSERT( PRIORITY_LOWEST <= priority && priority <= PRIORITY_HIGHEST  );
    priority_ = priority;
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
void RenderLayer::updateLayers(
    RenderLayers& layers,
    tick_t delta_time
){
    for (auto layer : layers) {
        if (!layer->isPauseLayer()) {
            layer->updateLayer(delta_time);
        }
    }
}
    
void RenderLayer::drawLayers(
    RenderLayers& layers
){
    for (auto layer : layers) {
        if (layer->isVisibleLayer()) {
            layer->drawLayer();
        }
    }
}


    
    
void RenderLayer::attachSystem() {
    t3::Director::instance().attachLayer(this);
}

void RenderLayer::detachSystem() {
    t3::Director::instance().detachLayer(this);
}


}   // inline namespace gfx
}   // namespace t3

