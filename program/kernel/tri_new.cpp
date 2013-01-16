#include <cstddef>

#include "base/tri_types.hpp"
#include "tri_heap.hpp"
#include "tri_heap_factory.hpp"
#include "dbg/tri_assert.hpp"
#include <stdlib.h>
#include "tri_new.hpp"
#include "tri_trace.hpp"
#include "tri_memory.hpp"


void* operator new( size_t size )
{
//    return operator new( size, t3::HeapFactory::getDefaultHeap() );
    return t3::default_allocator_.alloc<t3::byte>( size, "unknown.", 0 );
} 



void* operator new( size_t size, t3::Heap* heap )
{
    return heap->allocate( size );
}

void* operator new( size_t size, const char* const filename, int line )
{
    void* p = t3::default_allocator_.alloc<t3::byte>( size, filename, line );
    return p;
}

void operator delete( void* mem )
{
//    t3::Heap::deallocate( mem );
    t3::default_allocator_.free( mem );
}

void operator delete( void* mem, const char* const filename, int line )
{
}