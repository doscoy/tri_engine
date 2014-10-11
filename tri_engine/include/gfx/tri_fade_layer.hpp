
#ifndef TRI_FADE_LAYER_HPP_INCLUDED
#define TRI_FADE_LAYER_HPP_INCLUDED


#include "tri_draw_layer.hpp"
#include "tri_color.hpp"


namespace t3 {
inline namespace gfx {


class FadeLayer
    : public DrawLayer
{
public:
    FadeLayer();
    FadeLayer(const String& name, const int priority);
    ~FadeLayer();


public:
    void setFadeSpeed(
        const int speed
    ) {
        fade_speed_ = speed;
    }
    
    void fadeIn(
        const t3::tick_t sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = true;
        fade_speed_ = t3::frameSec<60>() / sec * -1;
    }
    
    void fadeOut(
        const tick_t sec
    ) {
        alpha_ = fade_color_.alphaFloat();
        fading_ = true;
        fade_in_ = false;
        fade_speed_ = t3::frameSec<60>() / sec;
    }
    
    
    bool isFadeEnd() const {
        return fading_ == false;
    }
    
    bool isFadeInEnd() const {
        if (fade_in_) {
            if (fading_ == false) {
                return true;
            }
        }
        
        return false;
    }
    
    bool isFadeOutEnd() const {
        if (!fade_in_) {
            if (fading_ == false) {
                return true;
            }
        }
        return false;
    }
    

    void setFadeColor(
        int r,
        int g,
        int b
    ) {
        fade_color_.red(r);
        fade_color_.green(g);
        fade_color_.blue(b);
    }
    
    void setFadeColor(
        const Color& c
    ) {
        fade_color_ = c;
    }
    
    void setupFadeParam(
        float fade_alpha,
        const Color& c
    ) {
        fading_ = false;
        alpha_ = fade_alpha;
        fade_color_ = c;
    }


private:
    void fadeUpdate(DrawLayer* const, tick_t);
    void fadeRender(DrawLayer* const);



private:
    bool fading_;
    bool fade_in_;
    float fade_speed_;
    Color fade_color_;
    float alpha_;
};



}   // namespace gfx
}   // namesapce t3




#endif  // TRI_FADE_LAYER_HPP_INCLUDED
