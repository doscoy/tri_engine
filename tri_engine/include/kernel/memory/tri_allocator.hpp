
#ifndef TRI_ALLOCATOR_HPP_INCLUDED
#define TRI_ALLOCATOR_HPP_INCLUDED


#include <cstdlib>
#include "../../util/tri_uncopyable.hpp"
#include "../../util/tri_counter.hpp"


//==============================================================================
namespace t3 {
    

class Allocator
    : private Uncopyable
{
    
public:
    // *********************************************
    //  メモリ割り当て
    template <typename T>
    T* alloc( 
        std::size_t size,
        const char* const filename,
        int line
    ){
        void* address = std::malloc( size );

        return reinterpret_cast<T*>( address );
    }
    
    // *********************************************
    //  メモリ解放
    void free( void* address ) {
        

        std::free( address );
    }
    


    

    
};

}   // namespace t3

#endif // TRI_ALLOCATOR_HPP_INCLUDED

