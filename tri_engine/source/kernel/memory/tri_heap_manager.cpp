#include "kernel/memory/tri_heap_manager.hpp"


namespace t3 {


const char* DEFAULT_HEAP_NAME = "Default";
Heap* HeapManager::default_heap_ = nullptr;


void HeapManager::initialize() {

    default_heap_ = createNewHeap(DEFAULT_HEAP_NAME);
}


Heap* HeapManager::getDefaultHeap() {
    
    if (default_heap_ == nullptr) {
        initialize();
    }
    
    return default_heap_;
}

Heap* HeapManager::createHeap(
    const char* const name
) {
    Heap* heap = findHeap(name);
    if (heap == nullptr) {
        heap = createNewHeap(name);
    }
    
    return heap;
}




HeapContainer& HeapManager::heaps() {
    static HeapContainer heaps;
    return heaps;
}

Heap* HeapManager::createNewHeap(
    const char* const name
) {
    HeapContainer::iterator itr = heaps().begin();
    HeapContainer::iterator end = heaps().end();
    
    for (;itr != end; ++itr) {
        if (!itr->isActive()) {
            itr->activate(name);
            return static_cast<Heap*>(&(*itr));
        }
    }
    
    return nullptr;
}


Heap* HeapManager::findHeap(
    const char* const name
){
    HeapContainer::iterator itr = heaps().begin();
    HeapContainer::iterator end = heaps().end();
    
    for (;itr != end; ++itr) {
        if (itr->isActive() && !strcmp(name, itr->name())) {
            return itr;
        }
    }
    
    return nullptr;
}

Heap* HeapManager::getHeap(int index) {
    return &heaps().at(index);
}

void HeapManager::dumpAllocateInfo(
    const uint32_t filter_min
) {

    for (auto& heap : heaps()) {
        heap.dump(filter_min);
    }

}




}   // namespace t3
