#include "kernel/memory/tri_heap_factory.hpp"


namespace t3 {



Heap* HeapFactory::root_heap_ = nullptr;
Heap* HeapFactory::default_heap_ = nullptr;
std::array<Heap, 10> HeapFactory::heaps_;


void HeapFactory::initialize()
{
    root_heap_ = createNewHeap( "Root" );
    default_heap_ = createHeap( "Default" );
}


Heap* HeapFactory::getDefaultHeap()
{
    if ( default_heap_ == nullptr ){
        initialize();
    }
    
    return default_heap_;
}

Heap* HeapFactory::getRootHeap()
{
    if ( root_heap_ == nullptr ){
        initialize();
    }
    
    return root_heap_;
}


Heap* HeapFactory::createHeap(
    const char* const name,
    const char* const parent_name
){
    if ( root_heap_ == nullptr ){
        initialize();
    }
    
    Heap* parent = findHeap( parent_name );
    if ( parent == nullptr ){
        parent = createNewHeap( parent_name );
//        parent->attach( root_heap_ );
    }
    
    Heap* heap = findHeap( name );
    if ( heap == nullptr ){
        heap = createNewHeap( name );
    }
    
//    heap->attach( parent );
    return heap;
}



Heap* HeapFactory::createHeap(
    const char* const name
){
    return createHeap( name, "Root" );
}


Heap* HeapFactory::createNewHeap(
    const char* const name
){
    std::array<Heap, 10>::iterator itr = heaps_.begin();
    std::array<Heap, 10>::iterator end = heaps_.end();
    
    for( ; itr != end; ++itr ){
        if ( !itr->isActive() ){
            itr->activate( name );
            return static_cast<Heap*>(&(*itr));
        }
    }
    
    return nullptr;
}


Heap* HeapFactory::findHeap(
    const char* const name
){
    std::array<Heap, 10>::iterator itr = heaps_.begin();
    std::array<Heap, 10>::iterator end = heaps_.end();
    
    for( ; itr != end; ++itr ){
        if ( itr->isActive() && !strcmp( name, itr->name() ) ){
            return itr;
        }
    }
    
    return nullptr;
}




}   // namespace t3
