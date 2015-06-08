

#include "dbg/tri_debugmenu_label.hpp"
#include "dbg/tri_debugmenu_frame.hpp"
#include "dbg/tri_print.hpp"


namespace t3 {

    

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

void DebugMenuLabel::draw(
    const float x,
    const float y,
    const Color& color
) const {
    T3_PRINT_DISP(x, y, color, DEBUG_MENU_FONT_SIZE, getLabel().c_str());
}

}   // namespace t3

