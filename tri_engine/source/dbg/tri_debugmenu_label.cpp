

#include "dbg/tri_debugmenu_label.hpp"
#include "dbg/tri_debugmenu_frame.hpp"

namespace t3 {
inline namespace dbg {
    

DebugMenuLabel::DebugMenuLabel(
    DebugMenuFrame* parent,
    const String& label
)   : parent_(nullptr)
    , label_(label)
    , focus_callback_(this, &DebugMenuLabel::nullCallback)
    , unfocus_callback_(this, &DebugMenuLabel::nullCallback)

{
    if (parent) {
        attachSelf(*parent);
    }
}

DebugMenuLabel::~DebugMenuLabel()
{

}

void DebugMenuLabel::attachSelf(
    DebugMenuFrame& frame
) {
    frame.attachItem(*this);
}
    
void DebugMenuLabel::detachSelf(){
    T3_NULL_ASSERT(parent_);
    parent_->detachItem(*this);
}

}   // inline namespace dbg
}   // namespace t3

