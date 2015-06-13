/**
    @file tri_render_layer.hpp
    描画レイヤー基底.
*/

#ifndef TRI_RENDER_LAYER_HPP_INCLUDED
#define TRI_RENDER_LAYER_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "utility/tri_uncopyable.hpp"
#include "utility/tri_nameable.hpp"
#include "debug/tri_debugmenu_items.hpp"
#include <list>



TRI_CORE_NS_BEGIN


//  前方参照
class Surface;
class RenderLayer;
using RenderLayers = List<RenderLayer*>;

///
/// 描画レイヤーベース
class RenderLayer
    : private Uncopyable
{
public:
    ///
    /// 描画プライオリティ
    enum LayerPriority {
        PRIORITY_LOWEST      =  10, // 奥
        PRIORITY_SYS_BACK    =  50,
        PRIORITY_APP_BACK1   =  60,
        PRIORITY_APP_BACK2   =  65,
        PRIORITY_APP_BACK3   =  70,
        PRIORITY_APP_BACK4   =  75,
        PRIORITY_APP_BACK5   =  80,
        PRIORITY_APP_DEFAULT = 100,
        PRIORITY_APP_FRONT1  = 120,
        PRIORITY_APP_FRONT2  = 125,
        PRIORITY_APP_FRONT3  = 130,
        PRIORITY_APP_FRONT4  = 135,
        PRIORITY_APP_FRONT5  = 140,
        PRIORITY_APP_UI      = 160,
        PRIORITY_SYS_FRONT   = 170,
        PRIORITY_SYS_FADE    = 180,
        PRIORITY_DEBUG       = 200,
        PRIORITY_HIGHEST     = 240, // 手前
    };
    
public:
    ///
    /// コンストラクタ
    RenderLayer(const String& name, const int priority);
    
    ///
    /// コンストラクタ
    explicit RenderLayer(const String& name);
    
    ///
    /// デストラクタ
    virtual ~RenderLayer();

public:

    ///
    /// レンダーターゲットを設定
    void renderTarget(
        Surface* target
    ) {
        render_target_ = target;
    }
    
    ///
    /// レンダーターゲットを取得
    const Surface* renderTarget() const {
        return render_target_;
    }

    ///
    /// プライオリティを設定
    void priority(const int priority);
    
    ///
    /// プライオリティを取得
    int priority() const {
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
public:
    ///
    ///  全てのレイヤーを更新
    static void updateLayers(
        RenderLayers& layers,
        tick_t delta_time
    );
    
    ///
    /// 全てのレイヤーを描画
    static void drawLayers(
        RenderLayers& layers
    );
    
protected:

    
    ///
    /// 更新
    virtual void updateLayer(tick_t delta_time) {}
    
    ///
    /// 描画
    virtual void drawLayer() {}
    
    ///
    /// drawLayerを呼ぶ
    void callDraw();
    
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
    uint8_t priority_;
    
    ///
    /// 描画ターゲット
    Surface* render_target_;

    ///
    ///  デバッグメニュー登録用フレーム
    DebugMenuFrame dmf_me_;
    
    ///
    /// 表示デバッグ
    DebugMenuItem<bool> dmi_visible_;
    
    ///
    /// ポーズデバッグ
    DebugMenuItem<bool> dmi_pause_;

    std::string layer_name_;
};



TRI_CORE_NS_END


#endif // TRI_RENDER_LAYER_HPP_INCLUDED

