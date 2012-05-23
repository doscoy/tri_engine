
#include "base/tri_types.hpp"
#include "tri_heap.hpp"
#include <cstddef>
#include <stdlib.h>
#include "dbg/tri_assert.hpp"
#include <string.h>
#include "dbg/tri_trace.hpp"



namespace t3 {


struct AllocHeader
{
    int signature_;
    int alloc_number_;
    size_t size_;
    Heap* heap_;
    AllocHeader* next_;
    AllocHeader* prev_;
};

int Heap::next_alloc_number_ = 0;




Heap::Heap()
    : active_( false )
    , allocated_( 0 )
    , peak_( 0 )
    , instances_( 0 )
    , head_alloc_( nullptr )
    , parent_( nullptr )
    , first_child_( nullptr )
    , next_siblind_( nullptr )
    , prev_sibling_( nullptr )
{
    strcpy( heap_name_, "NonActiveHeap" );    
    T3_TRACE("heap ctor.");
}


void* Heap::allocate( size_t size )
{
    //  本当に確保するサイズ　リクエストサイズ＋ヘッダ情報
    size_t alloc_header_size = sizeof( AllocHeader );
    size_t request_bytes = size + alloc_header_size;

    //  メモリ確保
    byte* mem = reinterpret_cast<byte*>( malloc( request_bytes ) );
    AllocHeader* header = reinterpret_cast< AllocHeader* >( mem );

    //  ヘッダ情報書き込み
    header->signature_ = HEAP_SIGNATURE;
    header->heap_ = this;
    header->size_ = size;
    header->next_ = head_alloc_;
    header->prev_ = nullptr;
    header->alloc_number_ = next_alloc_number_++;
    
    
    //  ヘッダリストの先頭を更新
    if ( head_alloc_ ){
        head_alloc_->prev_ = header;
    }
    head_alloc_ = header;
    
    //  トータルの割り当てサイズ
    allocated_ += size;
    
    if ( allocated_ > peak_ ){
        peak_ = allocated_;
    }
    
    instances_ += 1;

    void* start_mem_block = mem + alloc_header_size;
    return start_mem_block;
}


void Heap::deallocate( void* mem )
{
    t3::AllocHeader* header = reinterpret_cast<t3::AllocHeader*>(( reinterpret_cast<t3::byte*>(mem) - sizeof( t3::AllocHeader )));
    T3_ASSERT( header->signature_ == t3::HEAP_SIGNATURE );
  
    header->heap_->deallocate( header );
}


void Heap::deallocate( AllocHeader* header )
{
    if ( header->prev_ == nullptr ){
        head_alloc_ = header->next_;
    }
    else {
        header->prev_->next_ = header->next_;
    }
    
    
    if ( header->next_ != nullptr ){
        header->next_->prev_ = header->prev_;
    }
    allocated_ -= header->size_;
    instances_ -= 1;
    
    free( header );
}

void Heap::activate( const char *const name )
{
    T3_NULL_ASSERT( name );
    T3_ASSERT( strlen(name) < NAME_LENGTH );
    
    strcpy( heap_name_, name );
    allocated_ = 0;
    peak_ = 0;
    instances_ = 0;
    active_ = true;
}

void Heap::deactivate()
{
    strcpy( heap_name_, "" );
    
    allocated_ = 0;
    peak_ = 0;
    instances_ = 0;
    active_ = false;
}


void Heap::attach(
    Heap* parent
){
    if ( parent == parent_ ){
        return;
    }
    
    if ( prev_sibling_ ){
        prev_sibling_->next_siblind_ = next_siblind_;
    }
    
    if ( parent_ ){
        if ( parent_->first_child_ == this ){
            parent_ = first_child_ = next_siblind_;
        }
    }
    
    next_siblind_ = parent->first_child_;
    prev_sibling_ = nullptr;
    parent_ = parent;
    parent->first_child_ = this;
    
}





}   // namespace t3



