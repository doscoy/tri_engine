
#ifndef TRI_DEBUGMENU_HPP_INCLUDED
#define TRI_DEBUGMENU_HPP_INCLUDED

#include "tri_debugmenu_frame.hpp"
#include "tri_debugmenu_items.hpp"
#include "tri_virtual_pad.hpp"

namespace t3 {


class DebugMenu
    : public Singleton<DebugMenu>
{
public:
    DebugMenu();
    ~DebugMenu();
    
public:
    void openMenu();
    void closeMenu();
    
    
    void enable( const bool enable ){
        enable_ = enable;
    }
    
    bool isEnable() const {
        return enable_;
    }
    
    bool isOpened() const {
        return open_;
    }

    DebugMenuFrame& getMenuRoot() {
        return menu_root_;
    }
    
    const DebugMenuFrame& getMenuRoot() const {
        return menu_root_;
    }
        
    void update( tick_t delta_time );
    
    void render();
    
    
    void attachFrame(
        DebugMenuFrame& frame
    ){
        frame.attachSelf( menu_root_ );
    }
    
    const VirtualPad* virtualPad() const {
        return &vpad_;
    }
            
private:
    VirtualPad vpad_;
    DebugMenuFrame menu_root_;
    bool enable_;
    bool open_;
    
    short left_offset_;
    
};





}   // namespace t3

#endif // TRI_DEBUGMENU_HPP_INCLUDED