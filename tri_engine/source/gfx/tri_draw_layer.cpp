//
//  tri_draw_layer.cpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/01/21.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#include "tri_draw_layer.hpp"


namespace t3 {
inline namespace gfx {

DrawLayer::DrawLayer()
    : DrawLayer("Draw", PRIORITY_APP_NORMAL)
{
}


DrawLayer::DrawLayer(
    const std::string name,
    const int priority
)   : RenderLayer(name, priority)
    , update_func_(this, &self_t::nullUpdate)
    , render_func_(this, &self_t::nullRender)
{
}

DrawLayer::~DrawLayer()
{

}


void DrawLayer::updateLayer(
    tick_t delta_time
) {
    update_func_.invoke(this, delta_time);
}

void DrawLayer::drawLayer() {
    render_func_.invoke(this);
}



}   // inline namespace gfx
}   // namespace t3

