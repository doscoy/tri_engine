#include <cstdlib>
#include <cstring>
#include "dbg/tri_trace.hpp"
#include "kernel/memory/tri_heap_factory.hpp"




#define NEW_TRACE(...) t3::traceTerminal(__VA_ARGS__)

void* operator new(
    ::std::size_t size
) {
    void* p = t3::HeapFactory::getDefaultHeap()->allocate(size);
    return p;
}

void operator delete(
    void* mem
) {
    t3::Heap::deallocate(mem);
}

void* operator new[](
    ::std::size_t size
) {
    void* p = t3::HeapFactory::getDefaultHeap()->allocate(size);
    return p;
}

void operator delete[](
    void* mem
) {
    t3::Heap::deallocate(mem);
}



void* operator new(
    size_t size,
    const char* const filename,
    int line
) {
    void* p = t3::HeapFactory::getDefaultHeap()->allocate(size);
    return p;
}

void operator delete(
    void* mem,
    const char* const filename,
    int line
) {
    t3::Heap::deallocate(mem);
}

void* operator new[](
    size_t size,
    const char* const filename,
    int line
) {
    void* p = t3::HeapFactory::getDefaultHeap()->allocate(size);
    return p;
}

void operator delete[](
    void* mem,
    const char* const filename,
    int line
) {
    t3::Heap::deallocate(mem);
}

