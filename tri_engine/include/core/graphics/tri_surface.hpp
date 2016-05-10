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

    ///
    /// コンストラクタ
    Surface() = delete;
protected:
    ///
    /// コンストラクタ
    Surface(float width, float height);


public:

    ///
    /// デストラクタ
    virtual ~Surface() = default;

public:
    ///
    /// 描画開始処理
    void beginRender();

    ///
    /// 描画前処理
    void preRender();

    ///
    /// 描画後処理
    void postRender();

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
    /// サイズ取得
    const Vec2& size() {
        return size_;
    }

    ///
    /// テクスチャ取得
    const Textures textures() const {
        return textures_;
    }

    ///
    /// テクスチャ取得
    virtual TexturePtr colorTexture() {
        //  無効なテクスチャを返す
        return TexturePtr();
    }
    
    ///
    /// テクスチャ取得
    virtual const TexturePtr colorTexture() const {
        //  無効なテクスチャを返す
        return TexturePtr();
    }

    ///
    /// デプステクスチャ取得
    virtual TexturePtr depthTexture() {
        //  無効なテクスチャを返す
        return TexturePtr();
    }
    
    ///
    /// デプステクスチャ取得
    virtual const TexturePtr depthTexture() const {
        //  無効なテクスチャを返す
        return TexturePtr();
    }


public:
    ///
    /// 初期化
    void initialize() {
        onInitialize();
    }

private:
    ///
    /// 初期化用オーバーライド
    virtual void onInitialize() {}

    ///
    /// 描画前初期化用オーバーライド
    virtual void onBeginRender() {}

    ///
    /// 描画開始用オーバーライド
    virtual void onPreRender() {}

    ///
    /// 描画終了用オーバーライド
    virtual void onPostRender() {}

    

protected:
    ///
    /// テクスチャ
    Textures textures_;

    ///
    /// サイズ
    Vec2 size_;
};

///
/// サーフェスポインタ型
using SurfacePtr = SharedPtr<Surface>;


///
/// フレームバッファサーフェス
class FrameBufferSurface
    : public Surface
{
protected:   
    ///
    /// コンストラクタ
    FrameBufferSurface(
        float width,
        float height
    );
    
public:
    ///
    /// デストラクタ
    ~FrameBufferSurface() = default;



protected:
    virtual void createTexture() = 0;
    virtual void attachTexture() = 0;
    virtual void clearSurfaceCore() = 0;

private:
    ///
    /// 初期化
    void onInitialize() override;
    
    ///
    /// 描画開始時処理
    void onBeginRender() override;
    
    ///
    /// 描画前処理
    void onPreRender() override;

    ///
    /// 描画後処理
    void onPostRender() override;




protected:
    ///
    /// クリア
    void clearSurface();

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
    /// 変更前のビューポート位置
    int last_viewport_pos_x_;
    int last_viewport_pos_y_;
    int last_viewport_width_;
    int last_viewport_height_;

    ///
    /// フレームバッファ
    FrameBuffer fb_;
        
    ///
    /// バインド中フラグ
    bool bound_;
    
    ///
    /// バッファクリア済フラグ
    bool buffer_cleared_;
};

class DepthSurface
    : public FrameBufferSurface
{
private:
    ///
    /// コンストラクタ
    DepthSurface(
        float width,
        float height
    );


protected:
    ///
    /// テクスチャ生成の詳細
    void createTexture() override;

    ///
    /// テクスチャアタッチの詳細
    void attachTexture() override;

    ///
    /// サーフェスのクリアの詳細
    void clearSurfaceCore() override;

public:
    ///
    /// デプステクスチャ取得
    TexturePtr depthTexture() override {
        return depth_texture_;
    }
    ///
    /// デプステクスチャ取得
    const TexturePtr depthTexture() const override {
        return depth_texture_;
    }

public:
    ///
    /// サーフェス生成
    static SurfacePtr create(float width, float height) {
        //  インスタンス生成
        SurfacePtr ptr(new DepthSurface(width, height));

        //  初期化
        ptr->initialize();
        return ptr;
    }

private:
    ///
    /// テクスチャ
    TexturePtr depth_texture_;

};

///
/// カラーアンドデプスバッファサーフェス
class ColorDepthSurface
    : public FrameBufferSurface
{
private:
    ///
    /// コンストラクタ
    ColorDepthSurface(
        float width,
        float height
    );

protected:
    void createTexture() override;
    void attachTexture() override;
    void clearSurfaceCore() override;


public:
    ///
    /// テクスチャ取得
    TexturePtr colorTexture() override {
        return color_texture_;
    }
    
    ///
    /// テクスチャ取得
    const TexturePtr colorTexture() const override {
        return color_texture_;
    }

    ///
    /// デプステクスチャ取得
    TexturePtr depthTexture() override {
        return depth_texture_;
    }
    
    ///
    /// デプステクスチャ取得
    const TexturePtr depthTexture() const override {
        return depth_texture_;
    }

public:
    ///
    /// サーフェス生成
    static SurfacePtr create(float width, float height) {
        //  インスタンス生成
        SurfacePtr ptr(new ColorDepthSurface(width, height));

        //  初期化
        ptr->initialize();
        return ptr;
    }

private:
    ///
    /// テクスチャ
    TexturePtr color_texture_;
    TexturePtr depth_texture_;

};



///
/// デバイスサーフェス
class DeviceSurface
    : public Surface
{
private:
    DeviceSurface();

private:
    void onInitialize() override;

public:
    ///
    /// サーフェス生成
    static SurfacePtr create() {
        //  インスタンス生成
        SurfacePtr ptr(new DeviceSurface);

        //  初期化
        ptr->initialize();
        return ptr;
    }
};





TRI_CORE_NS_END


#endif  // TRI_SURFACE_HPP_INCLUDED
