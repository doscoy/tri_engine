////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/base/tri_screen_manager.hpp"
#include "core/math/tri_math.hpp"


TRI_CORE_NS_BEGIN




///
/// コンストラクタ
ScreenManager::ScreenManager()
    : device_screen_size_()
    , virtual_screen_size_()
    , screen_revise_()
{}


///
/// スクリーン座標からビューポート座標へ変換
Vec2 ScreenManager::screenToViewport(
    const Vec2& screen_pos
) {
    return screen_pos / virtualScreenSize() * 2.0f;
}

///
/// ビューポート座標からスクリーン座標へ変換
Vec2 ScreenManager::viewportToScreen(
    const Vec2& viewport_pos
) {
    return viewport_pos * virtualScreenSize() * 0.5f;
}

///
/// スクリーン外判定
bool ScreenManager::isOutOfScreen(
    const Vec2 &screen_pos
) {
    Vec2 vpos = screenToViewport(screen_pos);
    if (!inRange(vpos.x_, -1.0f, 1.0f)) {
        return true;
    }
    else if (!inRange(vpos.y_, -1.0f, 1.0f)) {
        return true;
    }
    
    return false;
}


void ScreenManager::calcScreenRevise() {

    auto revise = device_screen_size_ / virtual_screen_size_;
    float div = revise.x_ > revise.y_ ? revise.x_ : revise.y_;
    screen_revise_.x_ = revise.y_ / div;
    screen_revise_.y_ = revise.x_ / div;
}

void ScreenManager::calcAspectMode() {
    constexpr float ASPECT_RATIO[ASPECT_MODE_NUM] = {
        (16.0f / 9.0f),
        (4.0f / 3.0f),
        (9.0f / 16.0f),
        (3.0f / 4.0f)
    };
    
    
    float device_aspect = device_screen_size_.x_ / device_screen_size_.y_;
    
    float near_aspect = 100.0f;
    int near_aspect_index = 0;
    for (int i = 0; i < ASPECT_MODE_NUM; ++i) {
        float diff = ASPECT_RATIO[i] - device_aspect;
        diff = absolute(diff);
        if (near_aspect > diff) {
            //  より近いアスペクト比を見つけた
            near_aspect = diff;
            near_aspect_index = i;
        }
    }
    
    aspect_mode_ = static_cast<AspectMode>(near_aspect_index);
    
}


///
/// スクリーンリサイズ
void ScreenManager::resizeScreen(
    const Vec2& screen
) {
    deviceScreenSize(screen);

    cross::RenderSystem::setViewport(
        0,
        0,
        static_cast<int>(screen.x_),
        static_cast<int>(screen.y_)
    );

}

TRI_CORE_NS_END




