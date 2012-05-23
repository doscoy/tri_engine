#include "tri_memory_block.hpp"



namespace  {
    
    
inline size_t roundup(
    size_t size,
    int allign
){
    return (size + ( allign - 1 )) &~ ( allign - 1 );
}
    

    
}   // unname namespace




namespace t3 {



MemoryBlock::MemoryBlock( void* start_addr, size_t size )
    : start_addr_( start_addr )
    , block_size_( size )
{
}


MemoryBlock::~MemoryBlock()
{
}


void* MemoryBlock::allocate(
    size_t size,
    int allign
){
    MemoryChain* free_chain_item = free_chain_;
    size_t allocate_request_size = roundup( size, allign );

    //  リクエストサイズ以上のメモリブロックを検索
    while ( free_chain_item ){
        if ( free_chain_->size_ > allocate_request_size ){
            //  あった
            //  フリーチェイン繋ぎ直し
//            MemoryChain* new_;
//            free_chain_item->prev_->next_ = &free_chain_item + allocate_request_size;
//            use_chain_->prev_ = free_chain_item;
        }
        free_chain_item = free_chain_item->next_;
    }
    
}

void MemoryBlock::deallocate(
    void* mem
){
    
}








}   // namespace t3