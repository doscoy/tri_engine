
#ifndef TRI_DEBUGMENU_LABEL_HPP_INCLUDED
#define TRI_DEBUGMENU_LABEL_HPP_INCLUDED

#include "tri_print.hpp"
#include "../util/tri_util.hpp"

#include <string.h>

#define DEBUG_MENU_FONT_SIZE    ::t3::dbg::DEBUG_FONT_POINT

namespace t3 {
inline namespace dbg {
    
    

class DebugMenuFrame;
class DebugMenuLabel
    : private Uncopyable
{
    using callback_t = MethodCallback<DebugMenuLabel>;

    DebugMenuLabel();
public:
    DebugMenuLabel(
        DebugMenuFrame* parent,
        const std::string& label
    );
    
    virtual ~DebugMenuLabel();
    

public:

    const std::string& getLabel() const {
        return label_;
    };
    
    short getLabelWidth() const {
        return label_.size();
    };
    
    DebugMenuFrame* getParent() {
        return parent_;
    }
    
    void setParent(DebugMenuFrame* parent){
        parent_ = parent;
    }

    virtual bool hasChild() const {
        return false;
    }
    
    void attachSelf(DebugMenuFrame& frame);
    
    void detachSelf();
    
    void setEnable(const bool enable) {
        enable_ = enable;
    }
    
    bool isEnable() const {
        return enable_;
    }
    
    virtual void update(){};
    virtual void draw(
        const float x,
        const float y,
        const Color& color
    ) const {
        printDisplay(x, y, color, DEBUG_MENU_FONT_SIZE, getLabel().c_str());
    }
    
    template <typename T>
    void setFocusCallback(
        T* owner,
        void (T::*callback)()
    ) {
        MethodCallback<T> cb(owner, callback);
        focus_callback_ = (callback_t&)cb;
    }

    
    template <typename T>
    void setUnfocusCallback(
        T* owner,
        void (T::*callback)()
    ) {
        MethodCallback<T> cb(owner, callback);
        unfocus_callback_ = (callback_t&)cb;
    }

    void focusCallback() {
        T3_ASSERT(focus_callback_.canInvoke());
        focus_callback_.invoke();
    }
    
    void unfocusCallback() {
        T3_ASSERT(unfocus_callback_.canInvoke());
        unfocus_callback_.invoke();
    }

private:
    void nullCallback() {}
    
protected:
    DebugMenuFrame* parent_;
    std::string label_;
    bool enable_;
    
    //  開閉コールバック
    callback_t focus_callback_;
    callback_t unfocus_callback_;

};


}   // inline namespace dbg
}   // namespace t3

#endif // TRI_DEBUGMENU_LABEL_HPP_INCLUDED