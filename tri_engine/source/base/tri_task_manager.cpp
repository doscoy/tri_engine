
#include "tri_task_manager.hpp"
#include <functional>

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

}   // namespace base
}   // namespace t3