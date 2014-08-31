#include "kernel/process/tri_mutex.hpp"
#include "kernel/memory/tri_new.hpp"



//  デフォルトnew/delete

void* operator new(
    ::std::size_t size
) {
    return operator new(size, t3::HeapManager::getDefaultHeap(), "unknown", -1);
}

void operator delete(
    void* mem
) noexcept {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

void* operator new[](
    ::std::size_t size
) {
    return operator new[](size, t3::HeapManager::getDefaultHeap(), "unknown", -2);
}

void operator delete[](
    void* mem
) noexcept {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}


//  カスタムnew/delete


void* operator new(
    size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    return heap->allocate(size, filename, line);
}

void operator delete(
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

void* operator new[](
    size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    return heap->allocate(size, filename, line);
}

void operator delete[](
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    t3::ScopedLock lock(t3::Heap::mutex());
    t3::Heap::deallocate(mem);
}

