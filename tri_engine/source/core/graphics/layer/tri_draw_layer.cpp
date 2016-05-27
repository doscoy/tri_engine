////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/layer/tri_draw_layer.hpp"


TRI_CORE_NS_BEGIN



DrawLayer::DrawLayer(
    const String& name,
    const Priority priority
)   : LayerBase(name, priority)
    , update_func_(nullptr)
    , render_func_(nullptr)
{}

DrawLayer::~DrawLayer()
{}


void DrawLayer::updateLayer(
    const FrameInfo& frame_info
) {
    if (update_func_) {
        update_func_->invoke();
    }
}

void DrawLayer::renderLayer() {
    if (render_func_) {
        render_func_->invoke();
    }
}


TRI_CORE_NS_END

