
#include "base/tri_event_listener.hpp"
#include "dbg/tri_trace.hpp"


namespace t3 {
inline namespace base {



EventSnooper::EventSnooper()
    : msg_buffer_()
{
}

EventSnooper::~EventSnooper()
{
}


bool EventSnooper::handleEvent(
    const EventInterface& event
) {
    T3_TRACE(
        "Event snoop: event %08x time %f type %8x[%s]\n",
        &event,
        event.getTimeStamp(),
        event.getEventType().key(),
        event.getEventType().string().c_str()
        
    );
    return false;
}

}   // namespace base
}   // namespace t3




