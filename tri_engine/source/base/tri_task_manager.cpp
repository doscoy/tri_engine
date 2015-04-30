
#include "base/tri_task_manager.hpp"
#include <functional>
#include "dbg/tri_print.hpp"


namespace t3 {


TaskManager::TaskManager()
    : taskes_()
    , pause_level_(PAUSE_NONE)
{
    safeAddListener(this, &TaskManager::onPause, PauseEvent::TYPE);
    safeAddListener(this, &TaskManager::onResume, ResumeEvent::TYPE);
}

TaskManager::~TaskManager() {
    //  残ってるタスク全部にkillを立ててから
    killAllTask();
    
    safeRemoveListener(this);
}


void TaskManager::attach(
    SharedPtr<Task> task)
{
    taskes_.push_back(task);
    task->attachTask(true);
    
    taskes_.sort(std::greater<SharedPtr<Task>>());
    
    //  タスク初期化
    task->taskInitialize();
}

void TaskManager::updateTask(const tick_t delta_time) {
    TaskList::iterator itr = taskes_.begin();
    TaskList::iterator end = taskes_.end();
    
    SharedPtr<Task> next;
    
    while (itr != end) {
        SharedPtr<Task> t(*itr);
        T3_NULL_ASSERT(t.get());
        ++itr;
        
        if (t->isTaskDead()) {
            next = t->nextTask();
            //  次のタスクが存在しているなら登録
            if (next) {
                t->nextTask(SharedPtr<Task>(nullptr));
                attach(next);
            }
            //  タスク後片付け
            t->taskTerminate();
            
            //  登録解除
            detach(t);
        }
        else if (t->activated()) {
            PauseLevel tlv = t->pauseLevel();
            if (tlv > pause_level_) {
                t->taskFrame(delta_time);
            }
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
        SharedPtr<Task> t(*itr);
        T3_PRINT_DISP(show_x * 120, show_y * 15, "%s", t->name().c_str());
        task_num += 1;
    }
#endif // DEBUG
}

void TaskManager::killAllTask() {
    TaskList::iterator itr = taskes_.begin();
    TaskList::iterator end = taskes_.end();
    
    while (itr != end) {
        SharedPtr<Task> t(*itr);
        ++itr;
        t->taskTerminate();
        detach(t);
    }
}


void TaskManager::onPause(const t3::Event& eve) {
    auto& pause_eve = static_cast<const PauseEvent&>(eve);
    pause_level_ = pause_eve.getPauseLevel();
}

void TaskManager::onResume(const t3::Event&) {
    pause_level_ = PAUSE_NONE;
}


}   // namespace t3