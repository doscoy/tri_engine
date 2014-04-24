
#include "tri_task_manager.hpp"
#include <functional>
#include "dbg/tri_print.hpp"


namespace t3 {
inline namespace base {

TaskManager::~TaskManager() {
    for (auto it : taskes_) {
        detach( it );
    }
}


void TaskManager::attach(
    std::shared_ptr<Task> task)
{
    taskes_.push_back(task);
    task->setAttachedTask(true);
    
    taskes_.sort(std::greater<std::shared_ptr<Task>>());
}

void TaskManager::updateTask(const tick_t delta_time) {
    TaskList::iterator itr = taskes_.begin();
    TaskList::iterator end = taskes_.end();
    
    std::shared_ptr<Task> next;
    
    while (itr != end) {
        std::shared_ptr<Task> t(*itr);
        ++itr;
        
        if (t->isDead()) {
            next = t->getNextTask();
            if (next) {
                t->setNextTask(std::shared_ptr<Task>(nullptr));
                attach(next);
            }
            t->taskTerminate();
            detach(t);
        }
        else if (t->isActiveTask() && !t->isPausedTask()) {
            t->taskFrame(delta_time);
        }
    }
    
}

void TaskManager::printTask() const {
    
    TaskList::const_iterator itr = taskes_.begin();
    TaskList::const_iterator end = taskes_.end();
    
    int task_num = 0;
    for (; itr != end; ++itr) {
        int show_x = task_num / 61;
        int show_y = task_num % 61;
        std::shared_ptr<Task> t(*itr);
        t3::printDisplay(show_x * 120, show_y * 15, "%s", t->getTaskName());
        task_num += 1;
    }
}

}   // namespace base
}   // namespace t3