////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/base/tri_task_manager.hpp"
#include <functional>
#include "core/debug/tri_print.hpp"


TRI_CORE_NS_BEGIN


///
/// コンストラクタ
TaskManager::TaskManager()
    : taskes_()
    , pause_level_(PAUSE_NONE)
{
    EventManager::addListener(this, &TaskManager::onPause, PauseEvent::TYPE);
    EventManager::addListener(this, &TaskManager::onResume, ResumeEvent::TYPE);
}

///
/// デストラクタ
TaskManager::~TaskManager() {

    EventManager::removeListener(this);
}


void TaskManager::attach(
    TaskPtr task)
{
    taskes_.push_back(task);
    taskes_.sort(std::greater<TaskPtr>());
}



void TaskManager::updateTask(const tick_t delta_time) {
    
    for (auto& t : taskes_) {
        
        PauseLevel tlv = t->pauseLevel();
        if (tlv > pause_level_) {
            t->taskFrame(delta_time);
        }
    }
    
}

void TaskManager::printTask() const {
    
#if DEBUG
    TaskList::const_iterator itr = taskes_.begin();
    TaskList::const_iterator end = taskes_.end();
    
    int task_num = 0;
    for (; itr != end; ++itr) {
        int show_x = task_num / 61;
        int show_y = task_num % 61;
        TaskPtr t(*itr);
        T3_PRINT_DISP(show_x * 120, show_y * 15, "%s", t->name().c_str());
        task_num += 1;
    }
#endif // DEBUG
}

void TaskManager::killAllTask() {

}


void TaskManager::onPause(const t3::EventPtr eve) {
    auto pause_eve = static_cast<const PauseEvent*>(eve.get());
    pause_level_ = pause_eve->getPauseLevel();
}

void TaskManager::onResume(const t3::EventPtr) {
    pause_level_ = PAUSE_NONE;
}

TRI_CORE_NS_END


