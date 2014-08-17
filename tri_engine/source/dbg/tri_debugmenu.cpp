
#include "dbg/tri_debugmenu.hpp"
#include "dbg/tri_print.hpp"
#include "gfx/tri_color.hpp"
#include "dbg/tri_debugpad.hpp"

namespace t3 {

DebugMenu::DebugMenu()
    : vpad_()
    , menu_root_(nullptr, "")
    , enable_(false)
    , open_(false)
    , left_offset_(0)
{
    vpad_.close();
}


DebugMenu::~DebugMenu()
{
    
}


void DebugMenu::openMenu()
{
#ifdef NDEBUG
    return;
#endif

    T3_TRACE( "debug menu open\n" );

    if ( isOpened() ) {
        T3_TRACE( "debug menu is already opened.\n" );
        return;
    }
    
    vpad_.open();
    
    menu_root_.openFrame();
    open_ = true;
    
}


void DebugMenu::closeMenu()
{
    T3_TRACE( "debug menu close\n" );

    if ( !isOpened() ){
        return;
    }
    
    vpad_.close();
    
    menu_root_.closeFrame();
    open_ = false;
}

void DebugMenu::update( tick_t delta_time )
{
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

void DebugMenu::render()
{
    if ( !isOpened() ){
        return;
    }
    menu_root_.drawFrame( 3, 30, Color::white() );
}




}   // namespace t3

