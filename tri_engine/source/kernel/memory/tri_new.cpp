#include <cstdlib>
#include <cstring>
#include "dbg/tri_trace.hpp"


#define DIRTY_ALLOCATE_MEMORY   1
#define NEW_TRACE(...) t3::traceTerminal(__VA_ARGS__)

void* operator new(
    ::std::size_t size
) {
//    NEW_TRACE("new %dbyte.\n",size);
    void* p = std::malloc(size);
#if DIRTY_ALLOCATE_MEMORY
    std::memset(p, 0xDEADBEEF, size);
#endif // DIRTY_ALLOCATE_MEMORY
    return p;
}

void operator delete(
    void* mem
) {
//    NEW_TRACE("delete.\n");
    std::free(mem);
}

void* operator new[](
    ::std::size_t size
) {
//    NEW_TRACE("new[] %dbyte.\n",size);
    void* p = std::malloc(size);
#if DIRTY_ALLOCATE_MEMORY
    std::memset(p, 0xDEADBEEF, size);
#endif // DIRTY_ALLOCATE_MEMORY
    return p;
}

void operator delete[](
    void* mem
) {
//    NEW_TRACE("delete.\n");
    std::free(mem);
}



void* operator new(
    size_t size,
    const char* const filename,
    int line
) {
    NEW_TRACE("new %dbyte %s(%d).\n", size, filename, line);
    void* p = std::malloc(size);
    return p;
}

void operator delete(
    void* mem,
    const char* const filename,
    int line
) {
    NEW_TRACE("delete %s(%d).\n", filename, line);
    std::free(mem);
}

void* operator new[](
    size_t size,
    const char* const filename,
    int line
) {
    NEW_TRACE("new[] %dbyte %s(%d).\n", size, filename, line);
    void* p = std::malloc(size);
    return p;
}

void operator delete[](
    void* mem,
    const char* const filename,
    int line
) {
    NEW_TRACE("delete[] %s(%d).\n", filename, line);
    std::free(mem);
}

