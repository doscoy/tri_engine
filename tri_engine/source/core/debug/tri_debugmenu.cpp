////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


//  include
#include "core/debug/tri_debugmenu.hpp"
#include "core/debug/tri_print.hpp"
#include "core/debug/tri_debugpad.hpp"
#include "core/debug/tri_trace.hpp"
#include "core/graphics/tri_color.hpp"

TRI_CORE_NS_BEGIN

///
/// コンストラクタ
DebugMenu::DebugMenu()
    : vpad_()
    , menu_root_(nullptr, "")
    , enable_(false)
    , open_(false)
    , left_offset_(0)
{

}

///
/// デストラクタ
DebugMenu::~DebugMenu() {
    
}

///
/// 初期化
void DebugMenu::initialize() {
    vpad_.reset(T3_SYS_NEW VirtualPad);
    vpad_->close();
}

///
/// 後片付け
void DebugMenu::terminate() {

}

///
/// メニューをひらく
void DebugMenu::openMenu() {
#ifndef TRI_DEBUG
    //  デバッグモード以外では開かない
    return;
#endif

    if (isOpened()) {
        T3_SYSTEM_WARNING( "debug menu is already opened.\n" );
        return;
    }
    
    //  バーチャルパッドを表示
    vpad_->open();
    
    //  メニューをひらく
    menu_root_.openFrame();
    open_ = true;
    
}

///
/// メニューを閉じる
void DebugMenu::closeMenu() {

    if (!isOpened()) {
        //  開いてなければ何もしない
        return;
    }
    
    //  バーチャルパッドを閉じる
    vpad_->close();
    
    //  メニューを閉じる
    menu_root_.closeFrame();
    open_ = false;
}

///
/// 更新
void DebugMenu::update(const FrameInfo& frame_info) {
    if (!isOpened()) {
        return;
    }
    
    //  特に何もフォーカスしてない状態でBが押されたらメニューを閉じる
    if (!menu_root_.isFocused()) {
        const Pad& pad = debugPad();
        if (pad.isTrigger(Pad::BUTTON_B)) {
            closeMenu();
        }
    }
    
    //  更新
    menu_root_.update();
    
}

///
/// 描画
void DebugMenu::render() {
    //  デバメが開いている状態なら画面に描画
    if (!isOpened()) {
        return;
    }
    menu_root_.drawFrame(3, 30, color_sample::white());
}




TRI_CORE_NS_END

