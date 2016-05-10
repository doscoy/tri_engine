 ////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_layer_base.hpp
    描画レイヤー基底.
*/

#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/utility/tri_nameable.hpp"
#include "core/debug/tri_debugmenu_items.hpp"
#include "cross/cross_std.hpp"
#include "core/graphics/tri_surface.hpp"

TRI_CORE_NS_BEGIN


//  前方参照

class LayerBase;
using Layers = List<LayerBase*>;

///
/// 描画レイヤーベース
class LayerBase
    : private Uncopyable
{
public:
    ///
    /// 描画プライオリティ
    enum class Priority {
        LOWEST      = 10, // 奥
        
        SYS_BACK    = 20,

        BACK1       = 100,
        BACK2,
        BACK3,
        BACK4,
        BACK5,

        DEFAULT     = 200,

        FRONT1      = 300,
        FRONT2,
        FRONT3,
        FRONT4,
        FRONT5,

        UI          = 400,

        SYS_FADE    = 2000,
        SYS_FRONT   = 3000,
        SYS_DEBUG   = 4000,
        
        HIGHEST     = 5000, // 手前
    };
    
    
    ///
    /// 描画ターゲットタイプ
    enum class RenderTargetType {
        DEFAULT,
        DEVICE,
        USER_CUSTOM
    };
    
public:
    ///
    /// コンストラクタ
    explicit LayerBase(const String& name, const Priority priority = LayerBase::Priority::DEFAULT);
    
    
    ///
    /// デストラクタ
    virtual ~LayerBase();

public:

    ///
    /// レンダーターゲットをシステムのサーフェスに設定
    void setupRenderTargetToSystem() {
        render_target_type_ = RenderTargetType::DEFAULT;
    }
    
    ///
    /// レンダーターゲットをデバイスに設定
    void setupRenderTargetToDevice() {
        render_target_type_ = RenderTargetType::DEVICE;
    }

    ///
    /// レンダーターゲットをユーザー指定のサーフェスにする
    void setupRenderTargetToUserCustom(
        SurfacePtr surface
    ) {
        render_target_ = surface;
        render_target_type_ = RenderTargetType::USER_CUSTOM;
    }
    
    ///
    /// レンダーターゲットを取得
    const SurfacePtr userRenderTarget() const {
        return render_target_;
    }

    ///
    /// プライオリティを設定
    void priority(const Priority priority);
    
    ///
    /// プライオリティを取得
    Priority priority() const {
        return priority_;
    }
    
    ///
    /// レイヤーを表示する
    void showLayer(){
        if (!visible_){
            visible_ = true;
        }
    }
    
    ///
    /// レイヤーを非表示にする
    void hideLayer() {
        if (visible_) {
            visible_ = false;
        }
    }
    
    ///
    /// 描画可能レイヤーか判定
    bool isVisibleLayer() const {
        return visible_;
    }
    
    ///
    /// ポーズ
    void pauseLayer() {
        if (!pause_) {
            pause_ = true;
        }
    }
    
    ///
    /// ポーズを解除
    void resumeLayer() {
        if (pause_){
            pause_ = false;
        }
    }
    
    
    ///
    /// レイヤーを有効化
    void enableLayer() {
        showLayer();
        resumeLayer();
    }
    
    ///
    /// レイヤーを無効化
    void disableLayer() {
        hideLayer();
        pauseLayer();
    }
    
    
    ///
    /// ポーズ判定
    bool isPauseLayer() const {
        return pause_;
    }
    
    ///
    /// デバッグメニューを登録
    virtual void registryToDebugMenu(
        DebugMenuFrame& parent
    );
    
    ///
    /// デバッグメニューを削除
    virtual void unregistryToDebugMenu();
    
    ///
    /// レイヤー名を取得
    std::string name() {
        return layer_name_;
    }
    
    ///
    /// レイヤー名を設定
    void name(std::string name) {
        layer_name_ = name;
    }


    ///
    /// 更新前コールバック設定
    template <typename T>
    void setPreUpdateCallback(
        T* instance,
        void (T::*callback)()
    ) {
        preupdate_callback_.reset(new MethodCallback<T>(instance, callback));
    }

    ///
    /// 更新後コールバック設定
    template <typename T>
    void setPostUpdateCallback(
        T* instance,
        void (T::*callback)()
    ) {
        postupdate_callback_.reset(new MethodCallback<T>(instance, callback));
    }

    ///
    /// 描画前コールバック設定
    template <typename T>
    void setPreRenderCallback(
        T* instance,
        void (T::*callback)()
    ) {
        prerender_callback_.reset(new MethodCallback<T>(instance, callback));
    }

    ///
    /// 描画後コールバック設定
    template <typename T>
    void setPostRenderCallback(
        T* instance,
        void (T::*callback)()
    ) {
        postrender_callback_.reset(new MethodCallback<T>(instance, callback));
    }

public:
    ///
    ///  全てのレイヤーを更新
    static void updateLayers(
        Layers& layers,
        const FrameInfo& frame_info
    );
    
    ///
    /// 全てのレイヤーを描画
    static void renderLayers(
        Layers& layers
    );
    
protected:

    void initializeRender();
    
    
    ///
    /// 更新
    virtual void updateLayer(const FrameInfo& frame_info) {}
    
    ///
    /// 描画
    virtual void renderLayer() {}
    
    ///
    /// 描画処理を呼ぶ
    void render();
    
    
    ///
    /// 指定したサーフェスに向けてrenderLayer()を呼ぶ
    void doRenderLayer(SurfacePtr surface);
    
    ///
    /// システムに追加
    void attachSystem();
    
    ///
    /// システムから削除
    void detachSystem();

    
protected:
    ///
    /// ポーズフラグ
    bool pause_;
    
    ///
    /// 描画フラグ
    bool visible_;
    
    ///
    /// プライオリティ
    Priority priority_;

    ///
    /// 描画ターゲット指定
    RenderTargetType render_target_type_;
    
    ///
    /// 描画ターゲット
    SurfacePtr render_target_;

    ///
    ///  デバッグメニュー登録用フレーム
    DebugMenuFrame dmf_me_;
    
    ///
    /// 表示デバッグ
    DebugMenuItem<bool> dmi_visible_;
    
    ///
    /// ポーズデバッグ
    DebugMenuItem<bool> dmi_pause_;

    ///
    /// レイヤー名
    std::string layer_name_;

    ///
    /// 更新前ユーザーコールバック
    UniquePtr<MethodCallbackBase> preupdate_callback_;

    ///
    /// 更新後ユーザーコールバック
    UniquePtr<MethodCallbackBase> postupdate_callback_;

    ///
    /// 描画前ユーザーコールバック
    UniquePtr<MethodCallbackBase> prerender_callback_;

    ///
    /// 描画後ユーザーコールバック
    UniquePtr<MethodCallbackBase> postrender_callback_;

};



TRI_CORE_NS_END


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

