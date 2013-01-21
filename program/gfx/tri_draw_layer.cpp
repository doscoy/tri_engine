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
    : RenderLayer( "Draw" )
    , update_func_( this, &self_t::nullUpdate )
    , render_func_( this, &self_t::nullRender )
{
    
    
}


DrawLayer::~DrawLayer()
{
    
    
}


void DrawLayer::updateLayer( tick_t tick )
{
    update_func_.invoke( this, tick );
}

void DrawLayer::drawLayer()
{
    render_func_.invoke( this );
}



}   // inline namespace gfx
}   // namespace t3