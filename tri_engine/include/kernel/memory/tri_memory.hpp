#ifndef TRI_MEMORY_HPP_INCLUDED
#define TRI_MEMORY_HPP_INCLUDED


#include "tri_heap_manager.hpp"
#include "tri_allocator.hpp"
#include "tri_heap.hpp"
#include "tri_heap_manager.hpp"
#include "tri_memory_block.hpp"
#include "tri_new.hpp"
#include "tri_safe_delete.hpp"


#define T3_ALLOC(size)    ::t3::HeapManager::getDefaultHeap()->allocate(size, __FILE__, __LINE__)
#define T3_FREE(addr)     ::t3::Heap::deallocate(addr)



#endif // TRI_MEMORY_HPP_INCLUDED