

#include "tri_develop_base.hpp"
#include "tri_debugmenu_items.hpp"
#include "../kernel/tri_game_system.hpp"
#include "../io/tri_pad.hpp"

namespace t3 {


void makeTargetValueString(
    const int target,
    char* buf,
    size_t buf_size
){
    snprintf( buf, buf_size, "%7d", target );
}
    
void makeTargetValueString(
    const double target,
    char* buf,
    size_t buf_size
){
    snprintf( buf, buf_size, "%7.3f", target );
}
    
void makeTargetValueString(
    const float target,
    char* buf,
    size_t buf_size
){
    snprintf( buf, buf_size, "%7.3f", target );
}
    
void makeTargetValueString(
    const bool target,
    char* buf,
    size_t buf_size
){
    snprintf( buf, buf_size, "%s", target ? "true" : "false" );
}
    

void DebugMenuButtonBase::update()
{
    const Pad& pad = GameSystem::getInstance().getPad();
    if ( pad.isTrigger( PAD_BUTTON_RIGHT ) ){
        invoke();
    }
    else if ( pad.isTrigger( PAD_BUTTON_LEFT ) ){
        parent_->setFocusItem( nullptr );
    }
}





}   // namespace t3

