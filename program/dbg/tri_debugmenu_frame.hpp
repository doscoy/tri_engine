
#ifndef TRI_DEBUGMENU_FRAME_HPP_INCLUDED
#define TRI_DEBUGMENU_FRAME_HPP_INCLUDED

#include "tri_develop_base.hpp"
#include "tri_debugmenu_label.hpp"
#include <list>

namespace t3 {
inline namespace dbg {
    
    
typedef std::list<DebugMenuLabel*> DebugMenuList;

class DebugMenuFrame 
    : public DebugMenuLabel
{
    friend void DebugMenuLabel::attachSelf(t3::DebugMenuFrame &frame);
    friend void DebugMenuLabel::dettachSelf();
    
public:
    DebugMenuFrame(
        DebugMenuFrame* parent,
        const char* const label
    );
    
    ~DebugMenuFrame();

public:
    void show();
    
    void hide();
    
    bool hasChild() const {
        return items_.size() > 0;
    }
    
    DebugMenuLabel* getFocusItem() {
        return focus_item_;
    }
    const DebugMenuLabel* getFocusItem() const {
        return focus_item_;
    }
    
    void setFocusItem(
        DebugMenuLabel* const item
    ){
        focus_item_ = item;
    }
        DebugMenuList& getItems() {
        return items_;
    }
    
    const DebugMenuList& getItems() const {
        return items_;
    }
    
    virtual void update() override;
    
    virtual void drawFrame( 
        const float x,
        const float y
    ) const;
    
    
private:
    void attachItem( DebugMenuLabel& item );
    
    void dettachItem( DebugMenuLabel& item );
    
    
    
private:
    DebugMenuList items_;
    DebugMenuLabel* focus_item_;
    int select_idx_;
};


}   // inline namespace dbg
}   // namespace t3

#endif // TRI_DEBUGMENU_FRAME_HPP_INCLUDED