

#include "gfx/tri_render_layer.hpp"
#include "base/tri_director.hpp"
#include "gfx/tri_surface.hpp"



namespace t3{
    

RenderLayer::RenderLayer(
    const String& layer_name,
    const int priority
)   : Nameable()
    , pause_(false)
    , visible_(true)
    , priority_(priority)
    , render_target_(nullptr)
    , dmf_me_(nullptr, layer_name)
    , dmi_visible_(&dmf_me_, "VISIBLE", visible_, 1)
    , dmi_pause_(&dmf_me_, "PAUSE", pause_, 1)
{
    name(layer_name);
    attachSystem();
}
    
RenderLayer::RenderLayer(const String& name)
    : RenderLayer(name, PRIORITY_APP_DEFAULT)
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

    for (auto& layer : layers) {
        T3_ASSERT(layer);
        if (layer->isVisibleLayer()) {
            layer->callDraw();
        }
    }
}

void RenderLayer::callDraw() {
    if (render_target_) {
        render_target_->bind();
        render_target_->clear();

        int x, y, w, h;
        cross::RenderSystem::getViewport(&x, &y, &w, &h);
        cross::RenderSystem::setViewport(0, 0, render_target_->width(), render_target_->height());

        drawLayer();

        render_target_->unbind();
        cross::RenderSystem::setViewport(x, y, w, h);
   
    } else {
        drawLayer();
    }
    

}
    
    
void RenderLayer::attachSystem() {
    t3::Director::instance().attachLayer(this);
}

void RenderLayer::detachSystem() {
    t3::Director::instance().detachLayer(this);
}


}   // namespace t3

