
#include "tri_develop_base.hpp"
#include "tri_debugmenu.hpp"
#include "tri_print.hpp"
#include "../gfx/tri_color.hpp"

namespace t3 {

DebugMenu::DebugMenu()
    : menu_root_( nullptr, "" )
    , enable_( false )
    , open_( false )
{
    
    
}


DebugMenu::~DebugMenu()
{
    
}


void DebugMenu::openMenu()
{
    T3_TRACE( "debug menu open" );

    if ( isOpened() ) {
        T3_TRACE( "debug menu is already opened." );
        return;
    }
    
    
    menu_root_.show();
    open_ = true;
    
}


void DebugMenu::closeMenu()
{
    T3_TRACE( "debug menu close" );

    if ( !isOpened() ){
        return;
    }
    
    menu_root_.hide();
    open_ = false;
}

void DebugMenu::update( tick_t tick )
{
    if ( !isOpened() ){
        return;
    }
    if ( menu_root_.getFocusItem() == nullptr ){
        const Pad& pad = GameSystem::getInstance().getPad();
        if ( pad.isTrigger( PAD_BUTTON_LEFT ) ){
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
    menu_root_.drawFrame(0, 50);
}




}   // namespace t3

