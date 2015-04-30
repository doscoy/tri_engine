
#ifndef TRI_PAUSE_LEVEL_HPP_INCLUDED
#define TRI_PAUSE_LEVEL_HPP_INCLUDED

#include "tri_event.hpp"

namespace t3 {



enum PauseLevel {
    PAUSE_NONE,
    
    PAUSE_LV_1 = 1,
    PAUSE_LV_2,
    PAUSE_LV_3,
    PAUSE_LV_4,
    PAUSE_LV_5,
    PAUSE_LV_6,
    PAUSE_LV_7,
    PAUSE_LV_8
};


class PauseEvent
    : public EventBase {
public:
    PauseEvent(PauseLevel lv)
        : pause_lv_(lv)
    {}

    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }

    PauseLevel getPauseLevel() const {
        return pause_lv_;
    }

private:
    PauseLevel pause_lv_;
};

class ResumeEvent
    : public EventBase {
public:
    ResumeEvent(PauseLevel lv)
        : pause_lv_(lv)
    {}
    
    static const EventType TYPE;
    const EventType& eventType() const override {
        return TYPE;
    }

    PauseLevel getPauseLevel() const {
        return pause_lv_;
    }
    
private:
    PauseLevel pause_lv_;
};


}   // namespace t3



#endif  // TRI_PAUSE_LEVEL_HPP_INCLUDED


