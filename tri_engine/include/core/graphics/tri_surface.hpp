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
    virtual ~Surface() = default;
    
public:
    virtual void onBeginRender() = 0;
    virtual void onPreRender() = 0;
    virtual void onPostRender() = 0;

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

protected:
    ///
    /// サーフェスタイプ
    Type type_;
};

///
/// サーフェス
class FrameBufferSurface
    : public Surface
{
public:   
    ///
    /// コンストラクタ
    FrameBufferSurface(
        float width,
        float height,
        Type type
    );
    
    ///
    /// デストラクタ
    ~FrameBufferSurface() = default;


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
    float width() const {
        return size_.x_;
    }
    
    ///
    /// 高さ取得
    float height() const {
        return size_.y_;
    }
    
    ///
    /// 描画開始時処理
    void onBeginRender() override;
    
    ///
    /// 描画前処理
    void onPreRender() override;

    ///
    /// 描画後処理
    void onPostRender() override;


    ///
    /// クリア
    void clearBuffer();


protected:

    ///
    /// バインド
    void bind();
    
    ///
    /// バインド解除
    void unbind();
    
    ///
    /// ビューポート設定
    void setupViewport();
    
    ///
    /// ビューポート設定解除
    void resetViewport();

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
    /// バッファクリア済フラグ
    bool buffer_cleared_;


};


class DeviceSurface
    : public Surface
{
public:
    void onBeginRender() override {}
    void onPreRender() override {}
    void onPostRender() override {}

};





TRI_CORE_NS_END


#endif  // TRI_SURFACE_HPP_INCLUDED
