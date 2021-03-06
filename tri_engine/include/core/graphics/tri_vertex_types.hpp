////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_vertex_types.hpp
    頂点属性の型.
*/
#ifndef TRI_VERTEX_TYPES_HPP_INCLUDED
#define TRI_VERTEX_TYPES_HPP_INCLUDED

//  include
#include "core/math/tri_vec2.hpp"
#include "core/math/tri_vec3.hpp"
#include "core/core_config.hpp"


TRI_CORE_NS_BEGIN


///
/// 頂点定義.
/// 座標とカラー、UV値を持つ
struct VertexP2CT {
    float x_;
    float y_;
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
    uint8_t a_;
    float tu_;
    float tv_;
};

///
/// 頂点定義.
/// 座標とUV値を持つ
struct VertexP2T {
    VertexP2T()
        : position_(0,0)
        , uv_(0,0)
    {}

    Vec2 position_;
    Vec2 uv_;
};

///
/// 頂点定義.
/// 座標と法線を持つ
struct VertexP3N {
    VertexP3N()
        : position_(0,0,0)
        , normal_(0,0,0)
    {}
    
    Vec3 position_;
    Vec3 normal_;

};

///
/// 頂点定義.
/// 座標と法線とUVを持つ
struct VertexP3NT {
    VertexP3NT()
        : position_(0,0,0)
        , normal_(0,0,0)
        , uv_(0,0)
    {}
    
    Vec3 position_;
    Vec3 normal_;
    Vec2 uv_;
};


TRI_CORE_NS_END




#endif // TRI_VERTEX_TYPES_HPP_INCLUDED