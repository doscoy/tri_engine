

#ifndef TRI_TASK_MANAGER_HPP_INCLUDED
#define TRI_TASK_MANAGER_HPP_INCLUDED


#include "tri_task.hpp"
#include "base/tri_std.hpp"


namespace t3 {


typedef List<TaskPtr> TaskList;

class TaskManager
    : Uncopyable {
public:
    TaskManager();
    ~TaskManager();
    
public:
    void attach(TaskPtr task);
    
    bool hasTask() {
        return !taskes_.empty();
    }
        
    void updateTask(const tick_t delta_time);
    
    
    void printTask() const;
    
    std::size_t count() const {
        return taskes_.size();
    }
    
    std::size_t count(std::function<bool(const TaskPtr)> func) const {
        return std::count_if(taskes_.begin(), taskes_.end(), func);
    }
    
    
protected:
    TaskList taskes_;
    
private:
    void detach(TaskPtr task) {
        taskes_.remove(task);
        task->attachTask(false);
    }
    
    void killAllTask();
    
    void onPause(const Event&);
    void onResume(const Event&);
    
private:
    PauseLevel pause_level_;
};

}   // namespace t3

#endif // TRI_PROCESS_MANAGER_HPP_INCLUDED