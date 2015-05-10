#ifndef TRI_VERTEX_TYPES_HPP_INCLUDED
#define TRI_VERTEX_TYPES_HPP_INCLUDED

//  include
#include "math/tri_vec3.hpp"

namespace t3 {

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
struct VertexP2T
{
    float x_;
    float y_;
    float u_;
    float v_;
};

///
/// 頂点定義.
/// 座標と法線を持つ
struct VertexP3N {

    Vec3 position_;
    Vec3 normal_;

};



}   // namespace t3





#endif // TRI_VERTEX_TYPES_HPP_INCLUDED