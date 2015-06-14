

#include "core/graphics/tri_fade_layer.hpp"
#include "core/debug/tri_draw_primitive.hpp"




TRI_CORE_NS_BEGIN



FadeLayer::FadeLayer()
    : FadeLayer("fade", PRIORITY_SYS_FADE)
{
}


FadeLayer::FadeLayer(
    const String& name,
    const int priority
)   : RenderLayer(name, priority)
    , fading_(false)
    , fade_in_(true)
    , fade_speed_(1.0f)
    , fade_color_(color_sample::black())
    , alpha_(0.0f)
{
    fade_color_.alphaFloat(alpha_);
}

FadeLayer::~FadeLayer() {

}


void FadeLayer::updateLayer(
    tick_t delta_time
) {
    if (!fading_) {
        return;
    }

    alpha_ += fade_speed_ * deltaRate(delta_time);

    //  フェード中
    if (fade_in_) {
        //  フェードイン
        if (alpha_ <= 0) {
            alpha_ = 0;
            fading_ = false;
        }
    }
    else {
        //  フェードアウト
        if (alpha_ > 1.0f) {
            alpha_ = 1.0f;
            fading_ = false;
        }
    }
    
    fade_color_.alphaFloat(alpha_);
}


void FadeLayer::drawLayer() {
    if (isZeroFloat(alpha_)) {
        return;
    }

    cross::RenderSystem::setBlend(true);
    cross::RenderSystem::setBlendFunctionType(
        cross::RenderSystem::BlendFunctionType::TYPE_SRC_ALPHA,
        cross::RenderSystem::BlendFunctionType::TYPE_ONE_MINUS_SRC_ALPHA
    );
    
    drawRectangleViewport(
        Vec2(-1,  1),
        Vec2( 1, -1),
        fade_color_
    );
}

TRI_CORE_NS_END





