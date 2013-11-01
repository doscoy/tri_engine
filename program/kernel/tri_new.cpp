#include <cstddef>

#include "base/tri_types.hpp"
#include "tri_heap.hpp"
#include "tri_heap_factory.hpp"
#include "dbg/tri_assert.hpp"
#include <stdlib.h>
#include "tri_new.hpp"
#include "tri_trace.hpp"
#include "tri_memory.hpp"



//#define NEW_TRACE(...) T3_TRACE(__VA_ARGS__)
#define NEW_TRACE(...)  ((void)0)


void* operator new( size_t size )
{
    void* p = t3::default_allocator_.alloc<int8_t>( size, "unknown.", 0 );
    NEW_TRACE("new 0x%x\n", p);
    return p;
} 



void* operator new( size_t size, t3::Heap* heap )
{
    void* p = heap->allocate( size );
    NEW_TRACE("heap new 0x%x\n", p);
    return p;
}

void* operator new( size_t size, const char* const filename, int line )
{
    void* p = t3::default_allocator_.alloc<int8_t>( size, filename, line );
    NEW_TRACE("rec new 0x%x\n", p);
    return p;
}

void operator delete( void* mem )
{
    NEW_TRACE("delete 0x%x\n", mem);
    t3::default_allocator_.free( mem );
}

void operator delete( void* mem, const char* const filename, int line )
{
}