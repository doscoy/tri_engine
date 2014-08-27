#include "kernel/memory/tri_heap_factory.hpp"
#include "kernel/process/tri_mutex.hpp"



void* operator new(
    ::std::size_t size
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete(
    void* mem
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

void* operator new[](
    ::std::size_t size
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete[](
    void* mem
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}



void* operator new(
    size_t size,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete(
    void* mem,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

void* operator new[](
    size_t size,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap* heap = t3::HeapFactory::getDefaultHeap();
    return heap->allocate(size);
}

void operator delete[](
    void* mem,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

