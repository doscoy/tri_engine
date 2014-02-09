

#ifndef TRI_PROCESS_HPP_INCLUDED
#define TRI_PROCESS_HPP_INCLUDED


#include "base/tri_types.hpp"
#include "util/tri_uncopyable.hpp"
#include <memory>


namespace t3 {
inline namespace base {


class Process
    : private Uncopyable
{
    friend class ProcessManager;

protected:
    int priority_;
    bool kill_;
    bool active_;
    bool paused_;
    bool inital_update_;
    bool attached_;
    std::shared_ptr<Process> next_;
    
public:
    Process( int priority )
        : priority_( priority )
        , kill_( false )
        , active_( true )
        , paused_( false )
        , inital_update_( true )
        , attached_( false )
    {}
        
    virtual ~Process()
    {}

public:

    int getPriority() const {
        return priority_;
    }
    
    void setPriority( const int priority ){
        priority_ = priority;
    }

    bool isDead() const {
        return kill_;
    }
    
    bool isActive() const {
        return active_;
    }
    
    void setActive( const bool active ) {
        active_ = active;
    }
    
    bool isAttached() const {
        return attached_;
    }
    
    void setAttached( const bool attached ) {
        attached_ = attached;
    }
    
    bool isPaused() const {
        return paused_;
    }
    bool isInitialized() const {
        return !inital_update_;
    }
    
    const std::shared_ptr<Process> getNextProcess() const {
        return next_;
    }
    
    const std::shared_ptr<Process> setNextProcess( std::shared_ptr<Process> next ) {
        next_ = next;
        return next_;
    }
    
    
public:
    virtual void onUpdate( tick_t tick ) {
        if ( inital_update_ ){
            onInitialize();
            inital_update_ = false;
        }
    }

    virtual void onInitialize() {}

    virtual void kill(){
        kill_ = true;
    };

    virtual void togglePause() {
        paused_ = !paused_;
    }

};







class WaitProcess
    : public Process
{
public:
    WaitProcess( const tick_t wait_time )
        : Process( 0 )
        , now_( 0 )
        , end_time_( wait_time )
    {}
    
public:
    virtual void onUpdate( const tick_t tick ) override {
        Process::onUpdate( tick );
        if ( active_ ){
            now_ += tick;
            if ( now_ >= end_time_ ){
                kill();
            }
        }
    }


private:
    float now_;
    float end_time_;

};

}   // namespace base
}   // namespace t3



#endif // TRI_PROCESS_HPP_INCLUDED






