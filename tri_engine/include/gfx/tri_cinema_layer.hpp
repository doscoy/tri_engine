/**
    @file tri_cinema_layer.hpp
    シネマレイヤー.
*/

#ifndef TRI_CINEMA_LAYER_HPP_INCLUDED
#define TRI_CINEMA_LAYER_HPP_INCLUDED


//  include
#include "tri_render_layer.hpp"
#include "tri_shader.hpp"
#include "tri_texture.hpp"
#include "tri_vertex_buffer.hpp"
#include "tri_index_buffer.hpp"

namespace t3 {
  

///
/// シネマレイヤー
///
/// @par 別レンダリングしたテクスチャを貼るレイヤーです。
/// むにゃむにゃわちゃわちゃ
class CinemaLayer
    : public RenderLayer {
    
public:
    ///
    /// コンストラクタ
    CinemaLayer();

    ///
    /// コンストラクタ. レイヤ名と優先度を設定
    CinemaLayer(
        const String& name, ///< レイヤー名
        const int priority  ///< 優先度
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
    void updateLayer(tick_t delta_time) override;

    ///
    /// 描画関数
    void drawLayer() override;
    

private:
    cross::RenderSystem::BufferID vao_;
    VertexBuffer vb_;

    ShaderPtr shader_;          ///< シェーダ
    ShaderPtr color_shader_;    ///< カラー値表示シェーダ
    ShaderPtr depth_shader_;    ///< デプス値表示シェーダ
    TexturePtr texture_;        ///< テクスチャ
};
  
  
}   // namespace t3



#endif  // TRI_CINEMA_LAYER_HPP_INCLUDED
