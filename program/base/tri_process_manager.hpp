

#ifndef TRI_PROCESS_MANAGER_HPP_INCLUDED
#define TRI_PROCESS_MANAGER_HPP_INCLUDED


#include "tri_process.hpp"
#include <memory>
#include <list>

namespace t3 {
inline namespace base {


typedef std::list<std::shared_ptr<Process>> ProcessList;

class ProcessManager
{
public:
    ProcessManager() = default;
    
public:
    void attach( std::shared_ptr<Process> process ) {
        processes_.push_back( process );
        process->setAttached( true );
    }
    
    bool hasProcesses(){
        return !processes_.empty();
    }
        
    void updateProcess( const tick_t tick );
    
    ~ProcessManager();
    
protected:
    ProcessList processes_;
    
private:
    void detach( std::shared_ptr<Process> process ) {
        processes_.remove( process );
        process->setAttached( false );
    }
};

}   // namespace base
}   // namespace t3

#endif // TRI_PROCESS_MANAGER_HPP_INCLUDED