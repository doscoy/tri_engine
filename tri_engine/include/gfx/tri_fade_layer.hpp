
#ifndef TRI_FADE_LAYER_HPP_INCLUDED
#define TRI_FADE_LAYER_HPP_INCLUDED

//  include
#include "tri_draw_layer.hpp"
#include "tri_color.hpp"


namespace t3 {

///
/// フェードレイヤー
class FadeLayer
    : public DrawLayer
{
public:
    ///
    /// コンストラクタ
    FadeLayer();

    ///
    /// コンストラクタ
    FadeLayer(const String& name, const int priority);

    ///
    /// デストラクタ
    ~FadeLayer();


public:
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
        const t3::tick_t sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = true;
        fade_speed_ = t3::frameSec<60>() / sec * -1;
    }
    
    ///
    /// フェードアウト
    void fadeOut(
        const tick_t sec
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


private:
    ///
    /// フェードの更新コールバック
    void fadeUpdate(DrawLayer* const, tick_t);

    ///
    /// フェードの描画コールバック
    void fadeRender(DrawLayer* const);



private:
    bool fading_;           ///< フェード中かどうかのフラグ
    bool fade_in_;          ///< フェードインかどうかのフラグ
    float fade_speed_;      ///< フェード速度
    Color fade_color_;      ///< フェードカラー
    float alpha_;           ///< 透明度
};


}   // namesapce t3




#endif  // TRI_FADE_LAYER_HPP_INCLUDED
