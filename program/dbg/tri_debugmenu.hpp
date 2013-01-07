
#ifndef TRI_DEBUGMENU_HPP_INCLUDED
#define TRI_DEBUGMENU_HPP_INCLUDED

#include "tri_develop_base.hpp"
#include "tri_debugmenu_frame.hpp"
#include "tri_debugmenu_items.hpp"

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
    
    
    void setEnable( const bool enable ){
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
        
    void update( tick_t tick );
    
    void render();
    
    
    void attachFrame(
        DebugMenuFrame& frame
    ){
        frame.attachSelf( menu_root_ );
    }
    
            
private:

    DebugMenuFrame menu_root_;
    bool enable_;
    bool open_;
    
    short leftOffset_;
    
};





}   // namespace t3

#endif // TRI_DEBUGMENU_HPP_INCLUDED