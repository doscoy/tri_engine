////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_debugmenu.hpp
    デバッグメニュー.
*/

#ifndef TRI_DEBUGMENU_HPP_INCLUDED
#define TRI_DEBUGMENU_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_debugmenu_frame.hpp"
#include "tri_debugmenu_items.hpp"
#include "tri_virtual_pad.hpp"




TRI_CORE_NS_BEGIN


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
    /// 初期化
    void initialize();
    
    ///
    /// 後片付け
    void terminate();


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
    DebugMenuFrame* rootMenu() {
        return &menu_root_;
    }
    
    ///
    /// ルートメニュー取得
    const DebugMenuFrame* rootMenu() const {
        return &menu_root_;
    }
       
    ///
    /// 更新
    void update(const FrameInfo& frame_info );
    
    ///
    /// 描画
    void render();
    
    ///
    /// フレームに追加
    void attachFrame(
        DebugMenuFrame* frame
    ) {
        frame->attachSelf(&menu_root_);
    }
    
    ///
    /// バーチャルパッド取得
    const UniquePtr<VirtualPad>& virtualPad() const {
        return vpad_;
    }
            
private:
    UniquePtr<VirtualPad> vpad_;    ///< バーチャルパッド
    DebugMenuFrame menu_root_;      ///< デバメルート
    bool enable_;                   ///< 有効判定
    bool open_;                     ///< オープン判定
    short left_offset_;             ///< 左端からのオフセット位置
    
};





TRI_CORE_NS_END


#endif // TRI_DEBUGMENU_HPP_INCLUDED
