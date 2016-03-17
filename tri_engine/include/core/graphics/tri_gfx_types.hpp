////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_gfx_types.hpp
    グラフィックス関連型定義.
*/

#ifndef TRI_GFX_TYPES_HPP_INCLUDED
#define TRI_GFX_TYPES_HPP_INCLUDED

#include "core/core_config.hpp"
TRI_CORE_NS_BEGIN


///
/// テクスチャ座標構造体
struct TextureUV {
    float u0_;
    float v0_;
    float u1_;
    float v1_;
};


TRI_CORE_NS_END

#endif  // TRI_GFX_TYPES_HPP_INCLUDED
