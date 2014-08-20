#ifndef TRI_MEMORY_HPP_INCLUDED
#define TRI_MEMORY_HPP_INCLUDED


#include "tri_heap_factory.hpp"
#include "tri_allocator.hpp"
#include "tri_heap.hpp"
#include "tri_heap_factory.hpp"
#include "tri_memory_block.hpp"
#include "tri_new.hpp"
#include "tri_safe_delete.hpp"


#define T3_ALLOC(size)    ::t3::HeapFactory::getDefaultHeap()->allocate(size)
#define T3_FREE(addr)     ::t3::Heap::deallocate(addr)



#endif // TRI_MEMORY_HPP_INCLUDED