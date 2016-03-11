////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_screen_manager.hpp
    スクリーンマネージャ.
*/

#ifndef TRI_SCREEN_MANAGER_HPP_INCLUDED
#define TRI_SCREEN_MANAGER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/math/tri_vec2.hpp"
#include "core/utility/tri_singleton.hpp"


TRI_CORE_NS_BEGIN

///
/// スクリーンマネージャ
class ScreenManager final
    : public Singleton<ScreenManager>
{
    //  friend
    friend class Singleton<ScreenManager>;
    
private:
    ///
    /// コンストラクタ
    ScreenManager();

public:
    enum AspectMode {
        
        MODE_16_9,  // 16:9 横
        MODE_4_3,   // 4:3 横
        MODE_9_16,  // 16:9 縦
        MODE_3_4,   // 4:3 縦
        
        ///
        ASPECT_MODE_NUM,
    };

public:
    ///
    /// スクリーンリサイズ
    void resizeScreen(const Vec2& screen);
    
    ///
    /// デバイスのスクリーンサイズ取得
    const Vec2& deviceScreenSize() const {
        return device_screen_size_;
    }
    
    ///
    /// 仮想スクリーンサイズ設定
    void virtualScreenSize(const Vec2 screen) {
        virtual_screen_size_ = screen;
        calcScreenRevise();
    }
    
    ///
    /// 仮想スクリーンサイズ取得
    const Vec2& virtualScreenSize() const {
        return virtual_screen_size_;
    }
    
    ///
    /// スクリーンの補正値取得
    const Vec2& screenRevise() const {
        return screen_revise_;
    }
    
    ///
    /// ビューポートの位置に変換
    Vec2 screenToViewport(const Vec2& screen_pos);
    
    ///
    /// スクリーンのピクセル位置へ変換
    Vec2 viewportToScreen(const Vec2& viewport_pos);
    
    ///
    /// スクリーン外判定
    bool isOutOfScreen(const Vec2& screen_pos);

    ///
    /// アスペクトモードを取得
    AspectMode aspectMode() const {
        return aspect_mode_;
    }

    static constexpr int VIRTUAL_SCREEN_WIDTH_PORTRAIT = 640;
    static constexpr int VIRTUAL_SCREEN_HEIGHT_PORTRAIT = 1136;

    static constexpr int VIRTUAL_SCREEN_WIDTH_LANDSCAPE = 1920;
    static constexpr int VIRTUAL_SCREEN_HEIGHT_LANDSCAPE = 1080;

private:
    ///
    /// スクリーン拡大縮小率計算
    void calcScreenRevise();

    ///
    /// アスペクトモード調査
    void calcAspectMode();
    
    ///
    /// デバイスのスクリーンサイズ設定
    void deviceScreenSize(const Vec2& vp) {
        device_screen_size_ = vp;
        calcScreenRevise();
        calcAspectMode();
    }

private:
    //   スクリーンサイズ
    Vec2 device_screen_size_;           ///< デバイススクリーンサイズ
    Vec2 virtual_screen_size_;          ///< 仮想スクリーンサイズ
    Vec2 screen_revise_;
    AspectMode aspect_mode_;
};



TRI_CORE_NS_END

#endif // TRI_SCREEN_MANAGER_HPP_INCLUDED
