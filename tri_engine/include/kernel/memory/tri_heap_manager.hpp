
#ifndef TRI_HEAP_FACTORY_HPP_INCLUDED
#define TRI_HEAP_FACTORY_HPP_INCLUDED

#include "tri_heap.hpp"



namespace t3 {

enum HeapIndex {
    HEAP_DEFAULT,
    HEAP_SYS,
    HEAP_APP,
    HEAP_APP_EX1,
    HEAP_APP_EX2,
    HEAP_APP_EX3,
    HEAP_SIZE
};

using HeapContainer = Array<Heap, HEAP_SIZE>;

class HeapManager
{    

public:
    static Heap* createHeap(const char* const name);
    static void destroyHeap(Heap* heap);
    static Heap* getDefaultHeap();
    static Heap* getHeap(int index);
    static void dumpAllocateInfo(uint32_t filter_min);
    static HeapContainer& heaps();
    
private:
    static void initialize();
    static Heap* findHeap(const char* const name);
    static Heap* createNewHeap(const char* const name);

private:
    static Heap* default_heap_;
};


};

#endif // TRI_HEAP_FACTORY_HPP_INCLUDED

