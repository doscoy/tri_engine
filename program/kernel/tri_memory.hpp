#ifndef TRI_MEMORY_HPP_INCLUDED
#define TRI_MEMORY_HPP_INCLUDED

#include "tri_allocator.hpp"

namespace t3 {

extern Allocator default_allocator_;

#define T3_ALLOC( size )    default_allocator_.alloc<char>( size, __FILE__, __LINE__ )
#define T3_FREE( addr )     default_allocator_.free( addr )


}   // namespace t3



#endif // TRI_MEMORY_HPP_INCLUDED