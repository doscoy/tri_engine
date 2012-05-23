#include <cstddef>

#include "base/tri_types.hpp"
#include "tri_heap.hpp"
#include "tri_heap_factory.hpp"
#include "dbg/tri_assert.hpp"
#include <stdlib.h>
#include "tri_new.hpp"
#include "tri_trace.hpp"
void* operator new( size_t size )
{
    return operator new( size, t3::HeapFactory::getDefaultHeap() );
} 



void* operator new( size_t size, t3::Heap* heap )
{
    return heap->allocate( size );
}


void operator delete( void* mem )
{
    t3::Heap::deallocate( mem );
}