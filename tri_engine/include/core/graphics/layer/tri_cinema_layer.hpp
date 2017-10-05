////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_cinema_layer.hpp
    シネマレイヤー.
*/

#ifndef TRI_CINEMA_LAYER_HPP_INCLUDED
#define TRI_CINEMA_LAYER_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "core/graphics/layer/tri_layer_base.hpp"
#include "core/graphics/tri_shader.hpp"
#include "core/graphics/tri_texture.hpp"
#include "core/graphics/tri_vertex_buffer.hpp"
#include "core/graphics/tri_index_buffer.hpp"

TRI_CORE_NS_BEGIN

  

///
/// シネマレイヤー
///
/// @par 別レンダリングしたテクスチャを簡単に貼るレイヤーです。
class CinemaLayer;
using CinemaLayerPtr = SharedPtr<CinemaLayer>;
class CinemaLayer
    : public LayerBase {
    
private:
    ///
    /// コンストラクタ. レイヤ名と優先度を設定
    CinemaLayer(
        const String& name,             ///< レイヤー名
        const Priority priority         ///< 優先度
    );


    void initialize(
        const Position2D& min_pos,
        const Position2D& max_pos
    );

public:
    ///
    /// デストラクタ
    virtual ~CinemaLayer();


public:
    ///
    /// 使用するテクスチャを設定
    void texture(
        TexturePtr tex
    ) {
        texture_ = tex;
    }
    
    ///
    /// デフォルトのカラーシェーダを使用
    void useDefaultColorShader() {
        shader_ = color_shader_;
    }
    
    ///
    /// デフォルトのデプスシェーダを使用
    void useDefaultDepthShader() {
        shader_ = depth_shader_;
    }
    ///
    /// シェーダを設定
    void shader(ShaderPtr shader) {
        shader_ = shader;
    }

public:
    ///
    /// 生成関数
    static CinemaLayerPtr create(
        const Position2D& min_pos,
        const Position2D& max_pos,
        const String& name = "Cinema",
        const Priority priority = Priority::FRONT1
    ) {
        CinemaLayerPtr layer(T3_SYS_NEW CinemaLayer(name, priority));
        layer->initialize(min_pos, max_pos);
        return layer;
    }

    ///
    /// 生成関数
    static CinemaLayerPtr create() {
        return create(Position2D(-1, -1), Position2D(1, 1));
    }

private:
    ///
    /// 更新関数
    void updateLayer(const FrameInfo& frame_info) override;

    ///
    /// 描画関数
    void renderLayer() override;
    

private:
    cross::RenderSystem::BufferID vao_;
    VertexBuffer vb_;
    IndexBuffer ib_;

    ShaderPtr shader_;          ///< シェーダ
    ShaderPtr color_shader_;    ///< カラー値表示シェーダ
    ShaderPtr depth_shader_;    ///< デプス値表示シェーダ
    TexturePtr texture_;        ///< テクスチャ
};
  
  
TRI_CORE_NS_END



#endif  // TRI_CINEMA_LAYER_HPP_INCLUDED
