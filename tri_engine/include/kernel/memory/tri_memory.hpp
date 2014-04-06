#ifndef TRI_MEMORY_HPP_INCLUDED
#define TRI_MEMORY_HPP_INCLUDED

#include "tri_allocator.hpp"
#include "tri_allocation_recorder.hpp"
#include "tri_heap.hpp"
#include "tri_heap_factory.hpp"
#include "tri_memory_block.hpp"
#include "tri_new.hpp"
#include "tri_safe_delete.hpp"

namespace t3 {

extern Allocator default_allocator_;

#define T3_ALLOC(size)    default_allocator_.alloc<uint8_t>(size, __FILE__, __LINE__)
#define T3_FREE(addr)     default_allocator_.free(addr)


}   // namespace t3



#endif // TRI_MEMORY_HPP_INCLUDED