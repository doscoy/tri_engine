#include "kernel/memory/tri_heap_manager.hpp"


namespace t3 {


const char* DEFAULT_HEAP_NAME = "Def";
Heap* HeapManager::default_heap_ = nullptr;


void HeapManager::initialize() {

    heaps().at(0).activate(DEFAULT_HEAP_NAME, 0);
    default_heap_ = &heaps().at(0);

    heaps().at(1).activate("Sys", 1);
    heaps().at(2).activate("App", 2);
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
    
    int heap_idx = 0;
    for (;itr != end; ++itr) {
        heap_idx += 1;
        if (!itr->isActive()) {
            itr->activate(name, heap_idx);
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
            return &(*itr);
        }
    }
    
    return nullptr;
}

Heap* HeapManager::getHeap(int index) {
    return &heaps().at(index);
}

void HeapManager::dumpAllocateInfo(
    const uint32_t filter_min,
    const uint32_t filter_max
) {

    for (auto& heap : heaps()) {
        //  デフォルトヒープは追跡のしようがないので無視
        if (heap.no() == 0) {
            continue;
        }
        heap.dump(filter_min, filter_max);
    }

}




}   // namespace t3
