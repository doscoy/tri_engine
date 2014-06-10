
#include "base/tri_event_listener.hpp"
#include "base/tri_event_manager.hpp"
#include "dbg/tri_trace.hpp"


namespace t3 {
inline namespace base {


EventListener::~EventListener() {
    safeRemoveListener(this);
}



EventSnooper::EventSnooper()
    : msg_buffer_()
{
    setName("EventSnooper");
}

EventSnooper::~EventSnooper()
{
}


void EventSnooper::handleEvent(
    const Event& event
) {
    T3_TRACE(
        "EventBase snoop: event %08x time %f type %8x[%s]\n",
        &event,
        event.getTimeStamp(),
        event.getEventType().key(),
        event.getEventType().string().c_str()
        
    );
}

}   // namespace base
}   // namespace t3




