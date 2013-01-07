
#ifndef TRI_DEBUGMENU_FRAME_HPP_INCLUDED
#define TRI_DEBUGMENU_FRAME_HPP_INCLUDED

#include "tri_develop_base.hpp"
#include "tri_debugmenu_label.hpp"
#include <list>

namespace t3 {

typedef std::list<DebugMenuLabel*> DebugMenuList;

class DebugMenuFrame 
    : public DebugMenuLabel
{

public:
    DebugMenuFrame(
        DebugMenuFrame* parent,
        const char* const label
    );
    
    ~DebugMenuFrame();

public:
    void show();
    
    void hide();
    
    
    void attachItem( DebugMenuLabel* const item );
    
    void dettachItem( DebugMenuLabel* const item );
    
    void attachSelf( DebugMenuFrame& frame ){
        T3_ASSERT( parent_ == nullptr );
        parent_ = &frame;
        frame.attachItem( this );
    }
    
    void dettachSelf(){
        parent_->dettachItem( this );
    }
    
    
    
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
    DebugMenuList items_;
    DebugMenuLabel* focus_item_;
    int select_idx_;
};



}   // namespace t3

#endif // TRI_DEBUGMENU_FRAME_HPP_INCLUDED