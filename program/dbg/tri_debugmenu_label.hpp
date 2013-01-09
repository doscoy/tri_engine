
#ifndef TRI_DEBUGMENU_LABEL_HPP_INCLUDED
#define TRI_DEBUGMENU_LABEL_HPP_INCLUDED

#include "tri_develop_base.hpp"
#include "tri_print.hpp"
#include "../util/tri_uncopyable.hpp"
#include <string.h>

namespace t3 {
inline namespace dbg {
    
    

class DebugMenuFrame;
class DebugMenuLabel
    : private Uncopyable
{
public:
    DebugMenuLabel(
        DebugMenuFrame* parent,
        const char* const label
    );
    
    virtual ~DebugMenuLabel();
    

public:

    const char* getLabel() const {
        return label_;
    };
    
    short getLabelWidth() const {
        return label_length_;
    };
    
    DebugMenuFrame* getParent() {
        return parent_;
    }
    
    void setParent( DebugMenuFrame* parent ){
        parent_ = parent;
    }

    virtual bool hasChild() const {
        return false;
    }
    
    void attachSelf( DebugMenuFrame& frame );
    
    void dettachSelf();
    
    void setEnable( const bool enable ){
        enable_ = enable;
    }
    
    bool isEnable() const {
        return enable_;
    }
    
    virtual void update(){};
    virtual void draw(
        const float x,
        const float y
    ) const {
        printDisplay( x, y, getLabel() );
    }
    
protected:
    DebugMenuFrame* parent_;
    const char* label_;
    short label_length_;
    bool enable_;

};


}   // inline namespace dbg
}   // namespace t3

#endif // TRI_DEBUGMENU_LABEL_HPP_INCLUDED