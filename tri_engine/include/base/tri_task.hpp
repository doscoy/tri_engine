

#ifndef TRI_TASK_HPP_INCLUDED
#define TRI_TASK_HPP_INCLUDED


#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_nameable.hpp"
#include "tri_pause_level.hpp"
#include "tri_event_manager.hpp"
#include "base/tri_std.hpp"


namespace t3 {
inline namespace base {

class TaskManager;
class Task
    : private Uncopyable
    , virtual public Nameable
{
    friend class TaskManager;
    using self_t = Task;
public:

    enum Priority {
        PRIORITY_SYS_AFTER_APP  =    100,
        PRIORITY_APP_LOW        =  10000,
        PRIORITY_APP_DEFAULT    =  20000,
        PRIORITY_APP_HIGH       =  30000,
        PRIORITY_SYS_BEFORE_APP = 100000,
    };

public:
    Task(int type)
        : Task(type, PRIORITY_APP_DEFAULT, PAUSE_LV_1)
    {}
    
    Task()
        : Task(0, PRIORITY_APP_DEFAULT, PAUSE_LV_1)
    {}
    
    Task(
        int type,
        int priority,
        PauseLevel pause_lv
    )   : priority_(priority)
        , type_(type)
        , kill_(false)
        , active_(true)
        , inital_update_(true)
        , attached_(false)
        , pause_lv_(pause_lv)
    {
    }
        
    virtual ~Task()
    {
    }

public:

    int taskPriority() const {
        return priority_;
    }
    
    void taskPriority(const int priority){
        priority_ = priority;
    }
    
    int type() const {
        return type_;
    }
    
    void type(const int type) {
        type_ = type;
    }

    bool isTaskDead() const {
        return kill_;
    }
    
    bool activated() const {
        return active_;
    }
    
    void activate(const bool active) {
        active_ = active;
    }
    
    bool attachedTask() const {
        return attached_;
    }
    
    void attachTask(const bool attached) {
        attached_ = attached;
    }
    
    bool isTaskInitialized() const {
        return !inital_update_;
    }
    
    const SharedPtr<Task> nextTask() const {
        return next_;
    }
    
    const SharedPtr<Task> nextTask(SharedPtr<Task> next) {
        next_ = next;
        return next_;
    }
    
    void killTask() {
        kill_ = true;
    };
    
    PauseLevel pauseLevel() const {
        return pause_lv_;
    }
    
    void pauseLevel(const PauseLevel lv) {
        pause_lv_ = lv;
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
    int type_;
    bool kill_;
    bool active_;
    bool inital_update_;
    bool attached_;
    PauseLevel pause_lv_;
    SharedPtr<Task> next_;
    
};







class WaitingTask
    : public Task
{
public:
    WaitingTask(const tick_t wait_time)
        : Task()
        , now_(0)
        , end_time_(wait_time)
    {}
    
public:
    void taskUpdate(
        const tick_t delta_time
    ) override {
        if (activated()){
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

using TaskPtr = SharedPtr<Task>;

}   // namespace base
}   // namespace t3



#endif // TRI_TASK_HPP_INCLUDED






