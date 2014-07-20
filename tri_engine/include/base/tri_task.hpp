

#ifndef TRI_TASK_HPP_INCLUDED
#define TRI_TASK_HPP_INCLUDED


#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_nameable.hpp"
#include "tri_pause_level.hpp"
#include "tri_event_manager.hpp"
#include <memory>


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
    Task()
        : Task(PRIORITY_APP_DEFAULT, PAUSE_LV_1)
    {}
    
    Task(
        int priority,
        PauseLevel pause_lv
    )   : priority_(priority)
        , kill_(false)
        , active_(true)
        , paused_(false)
        , inital_update_(true)
        , attached_(false)
        , pause_lv_(pause_lv)
    {
        safeAddListener(this, &self_t::onPauseTask, PauseEvent::TYPE);
        safeAddListener(this, &self_t::onResumeTask, ResumeEvent::TYPE);
    }
        
    virtual ~Task()
    {
        safeRemoveListener(this, PauseEvent::TYPE);
        safeRemoveListener(this, ResumeEvent::TYPE);
    }

public:

    int taskPriority() const {
        return priority_;
    }
    
    void taskPriority(const int priority){
        priority_ = priority;
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
    
    bool isPausedTask() const {
        return paused_;
    }
    bool isTaskInitialized() const {
        return !inital_update_;
    }
    
    const std::shared_ptr<Task> nextTask() const {
        return next_;
    }
    
    const std::shared_ptr<Task> nextTask(std::shared_ptr<Task> next) {
        next_ = next;
        return next_;
    }
    
    void killTask() {
        kill_ = true;
    };
    


private:
    void onPauseTask(const Event& event);
    void onResumeTask(const Event& event);
    void pauseTask() {
        paused_ = true;
    }
    
    void resumeTask() {
        paused_ = false;
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
    PauseLevel pause_lv_;
    std::shared_ptr<Task> next_;
    char task_name_[16];

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

}   // namespace base
}   // namespace t3



#endif // TRI_TASK_HPP_INCLUDED






