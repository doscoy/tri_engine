

#include "tri_develop_base.hpp"
#include "tri_debugmenu_label.hpp"
#include "tri_debugmenu_frame.hpp"

namespace t3 {
inline namespace dbg {
    

DebugMenuLabel::DebugMenuLabel(
    DebugMenuFrame* parent,
    const char* const label
)   : parent_( parent )
    , label_( label )
    , focus_callback_(this, &DebugMenuLabel::nullCallback)
    , unfocus_callback_(this, &DebugMenuLabel::nullCallback)

{
    label_length_ = std::strlen( label_ );
    if ( parent ) {
        attachSelf( *parent );
    }
}

DebugMenuLabel::~DebugMenuLabel()
{
    if (parent_) {
        detachSelf();
    }
}

void DebugMenuLabel::attachSelf(
    DebugMenuFrame& frame
) {
    parent_ = &frame;
    frame.attachItem( *this );
}
    
void DebugMenuLabel::detachSelf(){
    T3_NULL_ASSERT(parent_);
    parent_->detachItem( *this );
    parent_ = nullptr;
}

}   // inline namespace dbg
}   // namespace t3

