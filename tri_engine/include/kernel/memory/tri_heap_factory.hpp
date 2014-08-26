
#ifndef TRI_HEAP_FACTORY_HPP_INCLUDED
#define TRI_HEAP_FACTORY_HPP_INCLUDED

#include "tri_heap.hpp"
#include <array>


namespace t3 {

class HeapFactory
{
    using HeapContainer = std::array<Heap, 5>;
public:
    static Heap* createHeap(const char* const name);
    static Heap* createHeap(const char* const name, const char* const parent_name);
    static void destroyHeap(Heap* heap);
    static Heap* getDefaultHeap();
    static Heap* getHeap(int index);
    static void dumpAllocateInfo();
    static void ASSERT_HEADER();
private:
    static void initialize();
    static Heap* findHeap(const char* const name);
    static Heap* createNewHeap(const char* const name);
    static Heap* getRootHeap();

private:
    static Heap* root_heap_;
    static Heap* default_heap_;
    static HeapContainer heaps_;
};


};

#endif // TRI_HEAP_FACTORY_HPP_INCLUDED

