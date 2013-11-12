

#include "tri_debugmenu_items.hpp"
#include "tri_debugpad.hpp"
#include "../kernel/io/tri_pad.hpp"

namespace t3 {
inline namespace dbg {

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
    const Pad& pad = debugPad();
    if ( pad.isRepeat( Pad::BUTTON_RIGHT ) ){
        invoke();
    }
    else if ( pad.isRepeat( Pad::BUTTON_LEFT ) ){
        parent_->setFocusItem( nullptr );
    }
}


}   // inline namespace dbg
}   // namespace t3

