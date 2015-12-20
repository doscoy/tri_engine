////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/base/tri_screen_manager.hpp"

TRI_CORE_NS_BEGIN


constexpr float VIRTUAL_SCREEN_WIDTH = 640.0f; ///< ゲーム内仮想スクリーンサイズ幅
constexpr float VIRTUAL_SCREEN_HEIGHT = 1136.0f; ///< ゲーム内仮想スクリーンサイズ高さ


///
///
ScreenManager::ScreenManager()
    : device_screen_size_(640.0f, 1136.0f)
    , virtual_screen_size_(
        VIRTUAL_SCREEN_WIDTH,
        VIRTUAL_SCREEN_HEIGHT)
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

    screen_revise_ = virtual_screen_size_ / device_screen_size_;
}



TRI_CORE_NS_END




