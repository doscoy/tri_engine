
#ifndef TRI_NEW_HPP_INCLUDED
#define TRI_NEW_HPP_INCLUDED

#include <cstddef>
#include "kernel/memory/tri_heap_manager.hpp"



#define T3_NEW          new(t3::HeapManager::getHeap(3) ,__FILE__, (int)__LINE__)
#define T3_SYS_NEW      new(t3::HeapManager::getHeap(2) ,__FILE__, (int)__LINE__)
#define T3_DELETE       delete
#define T3_DELETE_A     delete[]





extern void* operator new(
    ::std::size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
);
extern void operator delete(
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
);

extern void* operator new[](
    ::std::size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
);
extern void operator delete[](
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
);



#endif // TRI_NEW_HPP_INCLUDED