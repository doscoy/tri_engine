
#ifndef TRI_ALLOCATOR_HPP_INCLUDED
#define TRI_ALLOCATOR_HPP_INCLUDED


#include <cstdlib>
#include "../../util/tri_uncopyable.hpp"
#include "tri_allocation_recorder.hpp"
#include "../../util/tri_counter.hpp"


//==============================================================================
namespace t3 {
    

class Allocator : private Uncopyable
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
        allocation_recorder_.checkin( address, size, filename, line, frame_counter_.now() );
        return reinterpret_cast<T*>( address );
    }
    
    // *********************************************
    //  メモリ解放
    void free( void* address ) {
        
        allocation_recorder_.checkout( address );
        std::free( address );
    }
    
    // *********************************************
    //  アロケーションレコーダを取得
    const AllocationRecorder& getAllocationRecorder() const {
        return allocation_recorder_;
    }

    
private:
    AllocationRecorder allocation_recorder_;
    
};

}   // namespace t3

#endif // TRI_ALLOCATOR_HPP_INCLUDED

