////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/debug/tri_debugmenu_items.hpp"
#include "core/debug/tri_debugpad.hpp"
#include "core/kernel/io/tri_pad.hpp"

TRI_CORE_NS_BEGIN


///
/// 数値を文字列化
void makeTargetValueString(
    const int target,
    char* buf,
    size_t buf_size
) {
    snprintf(buf, buf_size, "%7d", target);
}

///
/// 数値を文字列化
void makeTargetValueString(
    const double target,
    char* buf,
    size_t buf_size
) {
    snprintf(buf, buf_size, "%7.3f", target);
}

///
/// 数値を文字列化
void makeTargetValueString(
    const float target,
    char* buf,
    size_t buf_size
) {
    snprintf(buf, buf_size, "%7.3f", target);
}

///
/// 数値を文字列化
void makeTargetValueString(
    const bool target,
    char* buf,
    size_t buf_size
) {
    snprintf( buf, buf_size, "%s", target ? "true" : "false" );
}
    
///
/// デバッグメニューボタン更新
void DebugMenuButtonBase::update() {
    const Pad& pad = debugPad();
    if ( pad.isRepeat(Pad::BUTTON_A)) {
        invoke();
    }
    else if (pad.isRepeat( Pad::BUTTON_B)) {
        parent_->setFocusItem(nullptr);
    }
}

TRI_CORE_NS_END
