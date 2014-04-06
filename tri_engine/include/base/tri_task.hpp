

#ifndef TRI_TASK_HPP_INCLUDED
#define TRI_TASK_HPP_INCLUDED


#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include <memory>


namespace t3 {
inline namespace base {


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
        : priority_(priority)
        , kill_(false)
        , active_(true)
        , paused_(false)
        , inital_update_(true)
        , attached_(false)
    {}
        
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

    
public:
    virtual void taskFrame(tick_t delta_time) {
        if (inital_update_){
            taskInitialize();
            inital_update_ = false;
        }
        taskUpdate(delta_time);
    }

    virtual void taskInitialize() {}
    virtual void taskUpdate(const tick_t delta_time) {}
    virtual void taskTerminate() {}
    
public:
    template <typename T>
    static std::shared_ptr<T> createTask() {
        std::shared_ptr<T> task;
        task.reset(new T);
        return task;
    }

    template <typename T, typename Arg>
    static std::shared_ptr<T> createTask(Arg arg) {
        std::shared_ptr<T> task;
        task.reset(new T(arg));
        return task;
    }


private:
    int priority_;
    bool kill_;
    bool active_;
    bool paused_;
    bool inital_update_;
    bool attached_;
    std::shared_ptr<Task> next_;

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






