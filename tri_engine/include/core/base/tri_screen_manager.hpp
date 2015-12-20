////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_screen_manager.hpp
    シーン.
*/

#ifndef TRI_SCREEN_MANAGER_HPP_INCLUDED
#define TRI_SCREEN_MANAGER_HPP_INCLUDED


#include "core/core_config.hpp"
#include "core/math/tri_vec2.hpp"
#include "core/utility/tri_singleton.hpp"


TRI_CORE_NS_BEGIN

///
/// ディレクター
class ScreenManager
    : public Singleton<ScreenManager>
{
    //  friend
    friend class Singleton<ScreenManager>;
    
public:
    ScreenManager();
    
    ///
    /// デバイスのスクリーンサイズ設定
    void deviceScreenSize(const Vec2& vp) {
        device_screen_size_ = vp;
        calcScreenRevise();
    }
    
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

private:
    ///
    /// スクリーン計算
    void calcScreenRevise();

private:
    //   スクリーンサイズ
    Vec2 device_screen_size_;           ///< デバイススクリーンサイズ
    Vec2 virtual_screen_size_;          ///< 仮想スクリーンサイズ
    Vec2 screen_revise_;

};



TRI_CORE_NS_END

#endif // TRI_SCREEN_MANAGER_INCLUDED
