////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_render_layer.hpp"
#include "core/base/tri_director.hpp"
#include "core/graphics/tri_surface.hpp"


TRI_CORE_NS_BEGIN

    

LayerBase::LayerBase(
    const String& layer_name,
    const int priority
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
    
LayerBase::LayerBase(const String& name)
    : LayerBase(name, PRIORITY_APP_DEFAULT)
{}



LayerBase::~LayerBase() {
    detachSystem();
}

void LayerBase::priority(
    const int priority
) {
    T3_ASSERT( PRIORITY_LOWEST <= priority && priority <= PRIORITY_HIGHEST  );
    priority_ = priority;
}



void LayerBase::registryToDebugMenu(
    DebugMenuFrame& parent
) {
    dmf_me_.attachSelf(parent);
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

void LayerBase::callDraw() {
    if (render_target_) {
        //  専用の描画ターゲットが指定されているので
        //  描画ターゲットの描画前後処理も呼ぶ
        render_target_->preRender();

        drawLayer();

        render_target_->postRender();
   
    } else {
        //  描画ターゲットの指定が無い場合はただ描画
        drawLayer();
    }
    

}
    
    
void LayerBase::attachSystem() {
    t3::Director::instance().attachLayer(this);
}

void LayerBase::detachSystem() {
    t3::Director::instance().detachLayer(this);
}


TRI_CORE_NS_END

