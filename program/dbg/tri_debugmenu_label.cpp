

#include "tri_develop_base.hpp"
#include "tri_debugmenu_label.hpp"
#include "tri_debugmenu_frame.hpp"

namespace t3 {

DebugMenuLabel::DebugMenuLabel(
    DebugMenuFrame* parent,
    const char* const label
)   : parent_( parent )
    , label_( label )
{
    label_length_ = std::strlen( label_ );
    if ( parent ) {
        parent->attachItem( this );
    }
}

DebugMenuLabel::~DebugMenuLabel()
{
    if ( parent_ ){
        parent_->dettachItem( this );
    }
}

}   // namespace t3

