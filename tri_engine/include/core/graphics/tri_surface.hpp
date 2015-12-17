////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_surface.hpp
    描画ターゲット.
*/

#ifndef TRI_SURFACE_HPP_INCLUDED
#define TRI_SURFACE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/graphics/tri_texture.hpp"
#include "tri_framebuffer.hpp"


TRI_CORE_NS_BEGIN


///
/// サーフェス
class Surface {
public:
    enum class Type {
        DEPTH_ONLY,
        COLOR_ONLY,
        COLOR_DEPTH
    };
public:
    ///
    /// コンストラクタ
    Surface();
    
    ///
    /// コンストラクタ
    Surface(
        float width,
        float height,
        Type type
    );
    
    ///
    /// デストラクタ
    ~Surface();


public:
    ///
    /// テクスチャ取得
    TexturePtr colorTexture() {
        return color_texture_;
    }
    
    ///
    /// テクスチャ取得
    const TexturePtr colorTexture() const {
        return color_texture_;
    }

    ///
    /// デプステクスチャ取得
    TexturePtr depthTexture() {
        return depth_texture_;
    }
    
    ///
    /// デプステクスチャ取得
    const TexturePtr depthTexture() const {
        return depth_texture_;
    }
    
    ///
    /// サイズ取得
    const Vec2& size() const {
        return size_;
    }
    
    ///
    /// 幅取得
    float width() {
        return size_.x_;
    }
    
    ///
    /// 高さ取得
    float height() {
        return size_.y_;
    }
    
    ///
    /// 描画前処理
    void preRender();

    ///
    /// 描画後処理
    void postRender();

    ///
    /// サーフェスのタイプ判定
    bool isDepthOnly() const {
        return type_ == Type::DEPTH_ONLY;
    }

    ///
    /// カラーのタイプ判定
    bool isColorOnly() const {
        return type_ == Type::COLOR_ONLY;
    }



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
    /// サイズ
    Vec2 size_;
    
    ///
    /// 変更前のビューポート位置
    int last_viewport_pos_x_;
    int last_viewport_pos_y_;
    int last_viewport_width_;
    int last_viewport_height_;

    ///
    /// フレームバッファ
    FrameBuffer fb_;
        
    ///
    /// テクスチャ
    TexturePtr color_texture_;
    TexturePtr depth_texture_;


    ///
    /// バインド中フラグ
    bool bound_;

    ///
    /// サーフェスタイプ
    Type type_;
};


TRI_CORE_NS_END


#endif  // TRI_SURFACE_HPP_INCLUDED
