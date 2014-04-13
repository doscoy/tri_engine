

#ifndef TRI_TASK_MANAGER_HPP_INCLUDED
#define TRI_TASK_MANAGER_HPP_INCLUDED


#include "tri_task.hpp"
#include <memory>
#include <list>


namespace t3 {
inline namespace base {


typedef std::list<std::shared_ptr<Task>> TaskList;

class TaskManager {
public:
    TaskManager() = default;
    
public:
    void attach(std::shared_ptr<Task> task);
    
    bool hasTask() {
        return !taskes_.empty();
    }
        
    void updateTask(const tick_t delta_time);
    
    ~TaskManager();
    
protected:
    TaskList taskes_;
    
private:
    void detach(std::shared_ptr<Task> task) {
        taskes_.remove(task);
        task->setAttachedTask(false);
    }
};

}   // namespace base
}   // namespace t3

#endif // TRI_PROCESS_MANAGER_HPP_INCLUDED