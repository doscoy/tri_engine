#ifndef TRI_MEMORY_POOL_HPP_INCLUDED
#define TRI_MEMORY_POOL_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include <cstddef>



namespace t3 {


struct MemoryChain
{
    void* addr_;
    MemoryChain* next_;
    MemoryChain* prev_;
    size_t size_;
};


class MemoryBlock
    : private Uncopyable
{
public:
    MemoryBlock( void* start_addr, size_t size );
    ~MemoryBlock();
    

public:
        
    const void* getStartAddress() {
        return start_addr_;
    }
    
    void* allocate(
        size_t size,
        int allign = 4
    );
    
    void deallocate(
        void* mem
    );
    
    
private:
    

private:
    const void* start_addr_;
    size_t block_size_;

    MemoryChain* use_chain_;
    MemoryChain* free_chain_;

};
    
    
    
    
    
    
    
    
}


#endif // TRI_MEMORY_POOL_HPP_INCLUDED