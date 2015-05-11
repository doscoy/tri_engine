/**
    @file tri_debugmenu.hpp
    デバッグメニュー.
*/

#ifndef TRI_DEBUGMENU_HPP_INCLUDED
#define TRI_DEBUGMENU_HPP_INCLUDED

//  include
#include "tri_debugmenu_frame.hpp"
#include "tri_debugmenu_items.hpp"
#include "tri_virtual_pad.hpp"

namespace t3 {

///
/// デバッグメニュー
class DebugMenu
    : public Singleton<DebugMenu>
{
public:
    ///
    /// コンストラクタ
    DebugMenu();

    ///
    /// デストラクタ
    ~DebugMenu();
    
public:
    ///
    /// メニューを開く
    void openMenu();

    ///
    /// メニューを閉じる
    void closeMenu();
    
    ///
    /// 有効設定
    void enable( const bool enable ){
        enable_ = enable;
    }
    
    ///
    /// 有効判定
    bool isEnable() const {
        return enable_;
    }
    
    ///
    /// オープン判定
    bool isOpened() const {
        return open_;
    }

    ///
    /// ルートメニュー取得
    DebugMenuFrame& rootMenu() {
        return menu_root_;
    }
    
    ///
    /// ルートメニュー取得
    const DebugMenuFrame& rootMenu() const {
        return menu_root_;
    }
       
    ///
    /// 更新
    void update( tick_t delta_time );
    
    ///
    /// 描画
    void render();
    
    ///
    /// フレームに追加
    void attachFrame(
        DebugMenuFrame& frame
    ){
        frame.attachSelf( menu_root_ );
    }
    
    ///
    /// バーチャルパッド取得
    const VirtualPad& virtualPad() const {
        return vpad_;
    }
            
private:
    VirtualPad vpad_;               ///< バーチャルパッド
    DebugMenuFrame menu_root_;      ///< デバメルート
    bool enable_;                   ///< 有効判定
    bool open_;                     ///< オープン判定
    
    short left_offset_;             ///< 左端からのオフセット位置
    
};





}   // namespace t3

#endif // TRI_DEBUGMENU_HPP_INCLUDED