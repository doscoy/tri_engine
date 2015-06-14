#include "core/kernel/process/tri_mutex.hpp"
#include "core/kernel/memory/tri_new.hpp"
#include "core/debug/tri_assert.hpp"


//  デフォルトnew/delete
/*
void* operator new(
    ::std::size_t size
) {
    return operator new(size, t3::HeapManager::getDefaultHeap(), "unknown", -1);
}

void operator delete(
    void* mem
) noexcept {
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
    t3::Heap::deallocate(mem);
}
*/

//  カスタムnew/delete


void* operator new(
    size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    void* mem = heap->allocate(size, filename, line);
    T3_NULL_ASSERT(mem);
    return mem;
}

void operator delete(
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    t3::Heap::deallocate(mem);
}

void* operator new[](
    size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
) {

    void* mem = heap->allocate(size, filename, line);
    T3_NULL_ASSERT(mem);
    return mem;
}

void operator delete[](
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
) {
    t3::Heap::deallocate(mem);
}

