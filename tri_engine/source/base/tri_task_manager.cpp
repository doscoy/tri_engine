
#include "tri_task_manager.hpp"
#include <functional>
#include "dbg/tri_print.hpp"


namespace t3 {
inline namespace base {

TaskManager::~TaskManager() {
    //  残ってるタスク全部にkillを立ててから
    killAllTask();
}


void TaskManager::attach(
    std::shared_ptr<Task> task)
{
    taskes_.push_back(task);
    task->attachTask(true);
    
    taskes_.sort(std::greater<std::shared_ptr<Task>>());
    
    //  タスク初期化
    task->taskInitialize();
}

void TaskManager::updateTask(const tick_t delta_time) {
    TaskList::iterator itr = taskes_.begin();
    TaskList::iterator end = taskes_.end();
    
    std::shared_ptr<Task> next;
    
    while (itr != end) {
        std::shared_ptr<Task> t(*itr);
        ++itr;
        
        if (t->isTaskDead()) {
            next = t->nextTask();
            //  次のタスクが存在しているなら登録
            if (next) {
                t->nextTask(std::shared_ptr<Task>(nullptr));
                attach(next);
            }
            //  タスク後片付け
            t->taskTerminate();
            
            //  登録解除
            detach(t);
        }
        else if (t->activated() && !t->isPausedTask()) {
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
        t3::printDisplay(show_x * 120, show_y * 15, "%s", t->name().c_str());
        task_num += 1;
    }
}

void TaskManager::killAllTask() {
    TaskList::iterator itr = taskes_.begin();
    TaskList::iterator end = taskes_.end();
    
    while (itr != end) {
        std::shared_ptr<Task> t(*itr);
        ++itr;
        t->taskTerminate();
        detach(t);
    }
}


}   // namespace base
}   // namespace t3