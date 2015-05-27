//
//  tri_draw_layer.cpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/01/21.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#include "gfx/tri_draw_layer.hpp"


namespace t3 {

DrawLayer::DrawLayer()
    : DrawLayer("Draw", PRIORITY_APP_DEFAULT)
{
}


DrawLayer::DrawLayer(
    const String name,
    const int priority
)   : RenderLayer(name, priority)
    , update_func_(nullptr)
    , render_func_(nullptr)
{
}

DrawLayer::~DrawLayer()
{

}


void DrawLayer::updateLayer(
    tick_t delta_time
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


}   // namespace t3

