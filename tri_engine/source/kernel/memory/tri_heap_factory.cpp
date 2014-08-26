#include "kernel/memory/tri_heap_factory.hpp"


namespace t3 {



Heap* HeapFactory::root_heap_ = nullptr;
Heap* HeapFactory::default_heap_ = nullptr;
HeapFactory::HeapContainer HeapFactory::heaps_;


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

    }
    
    Heap* heap = findHeap( name );
    if ( heap == nullptr ){
        heap = createNewHeap( name );
    }
    

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
    HeapContainer::iterator itr = heaps_.begin();
    HeapContainer::iterator end = heaps_.end();
    
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
    HeapContainer::iterator itr = heaps_.begin();
    HeapContainer::iterator end = heaps_.end();
    
    for( ; itr != end; ++itr ){
        if ( itr->isActive() && !strcmp( name, itr->name() ) ){
            return itr;
        }
    }
    
    return nullptr;
}

Heap* HeapFactory::getHeap(int index) {
    return &heaps_.at(index);
}

void HeapFactory::dumpAllocateInfo() {

    for (auto& heap : heaps_) {
        heap.dump();
    }

}

void HeapFactory::ASSERT_HEADER() {

//    for (auto& heap : heaps_) {
//        heap.ASSERT_HEADER();
//    }


//    heaps_[3].ASSERT_HEADER();

}


}   // namespace t3
