/**
    @file tri_surface.hpp
    描画ターゲット.
*/

#ifndef TRI_SURFACE_HPP_INCLUDED
#define TRI_SURFACE_HPP_INCLUDED

//  include
#include "gfx/tri_texture.hpp"

namespace t3 {

///
/// サーフェス
class Surface {

public:
    ///
    /// コンストラクタ
    Surface();
    
    ///
    /// コンストラクタ
    Surface(
        float width,
        float height
    );
    
    ///
    /// デストラクタ
    ~Surface();


public:
    ///
    /// テクスチャ取得
    TexturePtr texture() {
        return texture_;
    }
    
    ///
    /// テクスチャ取得
    const TexturePtr texture() const {
        return texture_;
    }
    
    ///
    /// 幅取得
    float width() {
        return width_;
    }
    
    ///
    /// 高さ取得
    float height() {
        return height_;
    }
    
    ///
    /// 描画前処理
    void preRender();

    ///
    /// 描画後処理
    void postRender();

private:

    ///
    /// バインド
    void bind();
    
    ///
    /// バインド解除
    void unbind();
    
    ///
    /// クリア
    void clear();

private:
    ///
    /// 幅
    float width_;
    
    ///
    /// 高さ
    float height_;
    
    ///
    /// フレームバッファ
    cross::RenderSystem::FrameBufferID fb_;
    
    ///
    /// カラーバッファ
    cross::RenderSystem::RenderBufferID cb_;
    
    ///
    /// デプスバッファ
    cross::RenderSystem::RenderBufferID depth_;
    
    ///
    /// フレームバッファ
    cross::RenderSystem::FrameBufferID last_fb_;
    
    ///
    /// レンダーバッファ
    cross::RenderSystem::RenderBufferID last_rb_;
    
    ///
    /// テクスチャ
    TexturePtr texture_;


    ///
    /// バインド中フラグ
    bool bound_;
};


}   // namespace t3


#endif  // TRI_SURFACE_HPP_INCLUDED
