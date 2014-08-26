#include <cstdlib>
#include <cstring>
#include "dbg/tri_trace.hpp"
#include "kernel/memory/tri_heap_factory.hpp"
#include "kernel/process/tri_mutex.hpp"

using AutoLock = std::lock_guard<t3::Mutex>;


#define NEW_TRACE(...) t3::traceTerminal(__VA_ARGS__)

void* operator new(
    ::std::size_t size
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete(
    void* mem
) {
//    AutoLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

void* operator new[](
    ::std::size_t size
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete[](
    void* mem
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}



void* operator new(
    size_t size,
    const char* const filename,
    int line
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete(
    void* mem,
    const char* const filename,
    int line
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

void* operator new[](
    size_t size,
    const char* const filename,
    int line
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete[](
    void* mem,
    const char* const filename,
    int line
) {
    AutoLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

