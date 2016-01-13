////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_layer_base.hpp"
#include "core/base/tri_director.hpp"
#include "core/graphics/tri_surface.hpp"


TRI_CORE_NS_BEGIN

LayerBase::LayerBase(
    const String& layer_name,
    const Priority priority
)   : pause_(false)
    , visible_(true)
    , priority_(priority)
    , render_target_(nullptr)
    , dmf_me_(nullptr, layer_name)
    , dmi_visible_(&dmf_me_, "VISIBLE", visible_)
    , dmi_pause_(&dmf_me_, "PAUSE", pause_)
    , layer_name_(layer_name)
    , preupdate_callback_(nullptr)
    , postupdate_callback_(nullptr)
    , prerender_callback_(nullptr)
    , postrender_callback_(nullptr)
{
    attachSystem();
}


LayerBase::~LayerBase() {
    detachSystem();
}

void LayerBase::priority(
    const Priority priority
) {
    T3_ASSERT(Priority::LOWEST <= priority && priority <= Priority::HIGHEST);
    priority_ = priority;
}



void LayerBase::registryToDebugMenu(
    DebugMenuFrame& parent
) {
    dmf_me_.attachSelf(&parent);
}

void LayerBase::unregistryToDebugMenu()
{
    dmf_me_.detachSelf();
}
    
    
    
//  レイヤー更新
void LayerBase::updateLayers(
    Layers& layers,
    DeltaTime delta_time
){
    for (auto& layer : layers) {
        //  ポーズしてるレイヤーはスキップ
        if (layer->isPauseLayer()) {
            continue;
        }

        //  更新前コールバック
        if (layer->preupdate_callback_) {
            layer->preupdate_callback_->invoke();
        }

        //  更新
        layer->updateLayer(delta_time);

        //  更新後コールバック
        if (layer->postupdate_callback_) {
            layer->postupdate_callback_->invoke();
        }
    }
}
    
void LayerBase::drawLayers(
    Layers& layers
) {
    for (auto& layer : layers) {
        layer->initializeRender();
    }


    for (auto& layer : layers) {
        T3_ASSERT(layer);

        //  表示オフしているレイヤーはスキップ
        if (!layer->isVisibleLayer()) {
            continue;
        }

        //  描画前コールバック
        if (layer->prerender_callback_) {
            layer->prerender_callback_->invoke();
        }

        //  描画
        layer->callDraw();

        //  描画後コールバック
        if (layer->postrender_callback_) {
            layer->postrender_callback_->invoke();
        }

    }
}


void LayerBase::initializeRender() {
    if (render_target_) {
        render_target_->onBeginRender();
    } else {
        Director::instance().finalSurface()->onBeginRender();
    }
}

void LayerBase::callDraw() {

    Surface* render_target = render_target_;
    
    if (!render_target) {
        //  レンダーターゲットの指定がない時はシステムの最終レンダーターゲット向けに描画する
        auto& director = Director::instance();
        auto& final_render_target = director.finalSurface();
        render_target = final_render_target.get();
    }

    render_target->onPreRender();

    drawLayer();

    render_target->onPostRender();
    

}
    
    
void LayerBase::attachSystem() {
    t3::Director::instance().attachLayer(this);
}

void LayerBase::detachSystem() {
    t3::Director::instance().detachLayer(this);
}


TRI_CORE_NS_END

