////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_draw_layer.hpp"


TRI_CORE_NS_BEGIN


DrawLayer::DrawLayer()
    : DrawLayer("Draw", PRIORITY_APP_DEFAULT)
{
}


DrawLayer::DrawLayer(
    const String name,
    const int priority
)   : LayerBase(name, priority)
    , update_func_(nullptr)
    , render_func_(nullptr)
{
}

DrawLayer::~DrawLayer()
{

}


void DrawLayer::updateLayer(
    DeltaTime delta_time
) {
    if (update_func_) {
        update_func_->invoke();
    }
}

void DrawLayer::drawLayer() {
    if (render_func_) {
        render_func_->invoke();
    }
}


TRI_CORE_NS_END

