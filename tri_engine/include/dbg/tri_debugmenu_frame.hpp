
#ifndef TRI_DEBUGMENU_FRAME_HPP_INCLUDED
#define TRI_DEBUGMENU_FRAME_HPP_INCLUDED

#include "tri_debugmenu_label.hpp"
#include <list>


namespace t3 {
inline namespace dbg {
    
    
typedef std::list<DebugMenuLabel*> DebugMenuList;

class DebugMenuFrame 
    : public DebugMenuLabel
{
    friend void DebugMenuLabel::attachSelf(t3::DebugMenuFrame &frame);
    friend void DebugMenuLabel::detachSelf();
    
public:
    DebugMenuFrame(
        DebugMenuFrame* parent,
        const char* const label
    );
    
    ~DebugMenuFrame();

public:
    void openFrame();
    
    void closeFrame();
    
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
        if (focus_item_) {
            focus_item_->unfocusCallback();
        }
        if (item) {
            item->focusCallback();
        }
        focus_item_ = item;
    }
    
    DebugMenuList& getItems() {
        return items_;
    }
    
    const DebugMenuList& getItems() const {
        return items_;
    }
    
    void update() override;
    
    void drawFrame( 
        const float x,
        const float y,
        const Color& color
    ) const;
    
    
private:
    void attachItem( DebugMenuLabel& item );
    
    void detachItem( DebugMenuLabel& item );
    
private:
    DebugMenuList items_;
    DebugMenuLabel* focus_item_;
    int select_idx_;


};


}   // inline namespace dbg
}   // namespace t3

#endif // TRI_DEBUGMENU_FRAME_HPP_INCLUDED