
#include "tri_process_manager.hpp"

namespace t3 {
inline namespace base {

ProcessManager::~ProcessManager()
{
    for ( auto it : processes_ ){
        detach( it );
    }
}


void ProcessManager::updateProcess( const tick_t tick )
{
    ProcessList::iterator itr = processes_.begin();
    ProcessList::iterator end = processes_.end();
    
    std::shared_ptr<Process> next;
    
    while ( itr != end ) {
        std::shared_ptr<Process> p( *itr );
        ++itr;
        
        if ( p->isDead() ){
            next = p->getNextProcess();
            if ( next ){
                p->setNextProcess( std::shared_ptr<Process>( nullptr ) );
                attach( next );
            }
            detach( p );
        }
        else if ( p->isActive() && !p->isPaused() ){
            p->onUpdate( tick );
        }
    }
    
}

}   // namespace base
}   // namespace t3