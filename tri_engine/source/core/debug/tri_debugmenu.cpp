////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/debug/tri_debugmenu.hpp"
#include "core/debug/tri_print.hpp"
#include "core/debug/tri_debugpad.hpp"
#include "core/debug/tri_trace.hpp"
#include "core/graphics/tri_color.hpp"

TRI_CORE_NS_BEGIN


DebugMenu::DebugMenu()
    : vpad_()
    , menu_root_(nullptr, "")
    , enable_(false)
    , open_(false)
    , left_offset_(0)
{

}


DebugMenu::~DebugMenu() {
    
}

void DebugMenu::initialize() {
    vpad_.reset(T3_SYS_NEW VirtualPad);
    vpad_->close();
}

void DebugMenu::terminate() {

}

void DebugMenu::openMenu() {
#ifndef DEBUG
    return;
#endif

    if (isOpened()) {
        T3_SYSTEM_WARNING( "debug menu is already opened.\n" );
        return;
    }
    
    vpad_->open();
    
    menu_root_.openFrame();
    open_ = true;
    
}


void DebugMenu::closeMenu() {

    if (!isOpened()) {
        return;
    }
    
    vpad_->close();
    
    menu_root_.closeFrame();
    open_ = false;
}

void DebugMenu::update(tick_t delta_time) {
    if (!isOpened()) {
        return;
    }
    
    if (menu_root_.getFocusItem() == nullptr) {
        const Pad& pad = debugPad();
        if (pad.isTrigger(Pad::BUTTON_B)) {
            closeMenu();
        }
    }
    
    menu_root_.update();
    
}

void DebugMenu::render() {
    if (!isOpened()) {
        return;
    }
    menu_root_.drawFrame(3, 30, color_sample::white());
}




TRI_CORE_NS_END

