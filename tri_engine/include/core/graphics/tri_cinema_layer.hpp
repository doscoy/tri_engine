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
#include "tri_layer_base.hpp"
#include "tri_shader.hpp"
#include "tri_texture.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"

TRI_CORE_NS_BEGIN

  

///
/// シネマレイヤー
///
/// @par 別レンダリングしたテクスチャを簡単に貼るレイヤーです。
class CinemaLayer
    : public LayerBase {
    
public:
    ///
    /// コンストラクタ
    CinemaLayer();

    ///
    /// コンストラクタ. レイヤ名と優先度を設定
    CinemaLayer(
        const Vec2 min_pos,                         ///< ビューポート座標最小値
        const Vec2 max_pos,                         ///< ビューポート座標最大値
        const String& name = "cinema",              ///< レイヤー名
        const Priority priority = Priority::FRONT1  ///< 優先度
    );

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
private:
    ///
    /// 更新関数
    void updateLayer(const DeltaTime delta_time) override;

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
