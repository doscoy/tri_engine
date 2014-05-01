

#ifndef TRI_TASK_HPP_INCLUDED
#define TRI_TASK_HPP_INCLUDED


#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include <memory>


namespace t3 {
inline namespace base {

class TaskManager;
class Task
    : private Uncopyable
{
    friend class TaskManager;
public:

    enum Priority {
        PRIORITY_SYS_AFTER_APP  =    100,
        PRIORITY_APP_LOW        =  10000,
        PRIORITY_APP_DEFAULT    =  20000,
        PRIORITY_APP_HIGH       =  30000,
        PRIORITY_SYS_BEFORE_APP = 100000,
    };


public:
    Task(int priority = PRIORITY_APP_DEFAULT)
        : Task("????", priority)
    {
    }
    
    Task(
        const char* const name,
        int priority = PRIORITY_APP_DEFAULT
    )   : priority_(priority)
        , kill_(false)
        , active_(true)
        , paused_(false)
        , inital_update_(true)
        , attached_(false)
    {
        setTaskName(name);
    }
        
    virtual ~Task()
    {}

public:

    int getTaskPriority() const {
        return priority_;
    }
    
    void setTaskPriority(const int priority){
        priority_ = priority;
    }

    bool isDead() const {
        return kill_;
    }
    
    bool isActiveTask() const {
        return active_;
    }
    
    void setActiveTask(const bool active) {
        active_ = active;
    }
    
    bool isAttachedTask() const {
        return attached_;
    }
    
    void setAttachedTask(const bool attached) {
        attached_ = attached;
    }
    
    bool isPausedTask() const {
        return paused_;
    }
    bool isTaskInitialized() const {
        return !inital_update_;
    }
    
    const std::shared_ptr<Task> getNextTask() const {
        return next_;
    }
    
    const std::shared_ptr<Task> setNextTask(std::shared_ptr<Task> next) {
        next_ = next;
        return next_;
    }
    
    void killTask() {
        kill_ = true;
    };
    
    void swithPause() {
        paused_ = !paused_;
    }

    void setTaskName(const char* const name) {
        std::strncpy(task_name_, name, 16);
    }
    
    const char* getTaskName() const {
        return task_name_;
    }

public:
    bool operator <(const Task& rhs) {
        return priority_ < rhs.priority_;
    }
    bool operator >(const Task& rhs) {
        return priority_ > rhs.priority_;
    }

public:
    virtual void taskFrame(tick_t delta_time) {
        taskUpdate(delta_time);
    }

    virtual void taskInitialize() {}
    virtual void taskUpdate(const tick_t delta_time) {}
    virtual void taskTerminate() {}
    

private:
    int priority_;
    bool kill_;
    bool active_;
    bool paused_;
    bool inital_update_;
    bool attached_;
    std::shared_ptr<Task> next_;
    char task_name_[16];

};







class WaitingTask
    : public Task
{
public:
    WaitingTask(const tick_t wait_time)
        : Task(0)
        , now_(0)
        , end_time_(wait_time)
    {}
    
public:
    void taskUpdate(
        const tick_t delta_time
    ) override {
        if (isActiveTask()){
            now_ += delta_time;
            if (now_ >= end_time_) {
                killTask();
            }
        }
    }


private:
    float now_;
    float end_time_;

};

}   // namespace base
}   // namespace t3



#endif // TRI_TASK_HPP_INCLUDED






