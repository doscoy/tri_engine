////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_fade_layer.hpp
    フェードレイヤー.
*/

#ifndef TRI_FADE_LAYER_HPP_INCLUDED
#define TRI_FADE_LAYER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/graphics/layer/tri_draw_layer.hpp"
#include "core/graphics/tri_color.hpp"


TRI_CORE_NS_BEGIN


///
/// フェードレイヤー
class FadeLayer;
using FadeLayerPtr = SharedPtr<FadeLayer>;
class FadeLayer
    : public LayerBase
{
protected:
    ///
    /// コンストラクタ
    FadeLayer(const String& name, const Priority priority);

public:
    ///
    /// デストラクタ
    ~FadeLayer();


public:

    
    ///
    /// 更新
    void updateLayer(const FrameInfo& frame_info) override;
    
    ///
    /// 描画
    void renderLayer() override;


    ///
    /// フェードスピード設定
    void setFadeSpeed(
        const float speed
    ) {
        fade_speed_ = speed;
    }
    
    ///
    /// フェードイン
    void fadeIn(
        const float sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = true;
        fade_speed_ = t3::frameSec<60>() / sec * -1;
    }
    
    ///
    /// フェードアウト
    void fadeOut(
        const float sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = false;
        fade_speed_ = t3::frameSec<60>() / sec;
    }
    
    
    ///
    /// フェード判定
    bool isFadeEnd() const {
        return fading_ == false;
    }
    
    ///
    /// フェードイン終了判定
    bool isFadeInEnd() const {
        if (fade_in_) {
            if (fading_ == false) {
                return true;
            }
        }
        
        return false;
    }
    
    ///
    /// フェードアウト終了判定
    bool isFadeOutEnd() const {
        if (!fade_in_) {
            if (fading_ == false) {
                return true;
            }
        }
        return false;
    }
    

    ///
    /// フェードカラーの設定
    void setFadeColor(
        int r,
        int g,
        int b
    ) {
        fade_color_.red(r);
        fade_color_.green(g);
        fade_color_.blue(b);
    }
    
    ///
    /// フェードカラーの設定
    void setFadeColor(
        const Color& c
    ) {
        fade_color_ = c;
    }
    
    ///
    /// フェードパラメータの設定
    void setupFadeParam(
        float fade_alpha,
        const Color& c
    ) {
        fading_ = false;
        alpha_ = fade_alpha;
        fade_color_ = c;
    }

public:
    ///
    /// 生成関数
    static FadeLayerPtr create(
        const String& name = "Fade",                    ///< 名前
        const Priority priority = Priority::SYS_FADE    ///< プライオリティ
    ) {
        FadeLayerPtr layer(T3_SYS_NEW FadeLayer(name, priority));
        layer->setupRenderTargetToSystem();
        return layer;
    }
private:
    bool fading_;           ///< フェード中かどうかのフラグ
    bool fade_in_;          ///< フェードインかどうかのフラグ
    float fade_speed_;      ///< フェード速度
    Color fade_color_;      ///< フェードカラー
    float alpha_;           ///< 透明度
};


TRI_CORE_NS_END




#endif  // TRI_FADE_LAYER_HPP_INCLUDED
