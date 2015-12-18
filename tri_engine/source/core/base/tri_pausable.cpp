////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/base/tri_pausable.hpp"
#include "core/base/tri_event_manager.hpp"


TRI_CORE_NS_BEGIN
TRI_EVENT_NS_BEGIN
        
const EventType PauseEvent::TYPE("tri_PauseEvent");
const EventType ResumeEvent::TYPE("tri_ResumeEvent");

TRI_EVENT_NS_END


///
/// Pausable
Pausable::Pausable()
    : pause_(false)
    , pause_lv_(PAUSE_LV_1)
{
    t3::EventManager::addListener(this, &Pausable::onPause, event::PauseEvent::TYPE);
    t3::EventManager::addListener(this, &Pausable::onResume, event::ResumeEvent::TYPE);
}


Pausable::~Pausable() {
    t3::EventManager::removeListener(this);
}



///
/// ポーズイベントハンドラ
void Pausable::onPause(
    const EventPtr e
) {
    const auto pause_event = static_cast<const event::PauseEvent*>(e.get());
    if (pause_event->getPauseLevel() >= pause_lv_) {
        pause();
    }
}


///
/// レジュームイベントハンドラ
void Pausable::onResume(
    const EventPtr e
) {
    const auto resume_event = static_cast<const event::ResumeEvent*>(e.get());
    if (resume_event->getPauseLevel() >= pause_lv_) {
        resume();
    }
}


TRI_CORE_NS_END
