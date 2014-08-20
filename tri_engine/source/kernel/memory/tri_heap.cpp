
#include "base/tri_types.hpp"
#include "kernel/memory/tri_heap.hpp"
#include "dbg/tri_assert.hpp"
#include "dbg/tri_trace.hpp"
#include <cstring>
#include <cstddef>
#include <cstdlib>

#define DIRTY_MEMORY 1
#define ALLOC_ENDMARKING    1


#define T3_MAKE_SIGNATURE4(a,b,c,d) ((uint32_t)((a) | ((b)<<8) | ((c)<<16) | ((d)<<24)))


namespace t3 {

constexpr uint32_t HEAP_SIGNATURE = T3_MAKE_SIGNATURE4('H','E','A','P');
constexpr uint32_t ALLOC_END_MARK = 0x99999999;
constexpr uint32_t DIRTY_ALLOC_MARK = 0xDEADBEEF;
constexpr uint32_t DIRTY_FREE_MARK = 0xCAFEC0DE;


class AllocHeader {
public:
    void setup(
        size_t size,
        Heap* heap,
        AllocHeader* next,
        AllocHeader* prev,
        const char* file,
        int line
    ) {
        signature_ = HEAP_SIGNATURE;
        size_ = size;
        heap_ = heap;
        next_ = next;
        prev_ = prev;
        file_name_ = file;
        line_ = line;
    }
    
    
    void changePreviousNext() {
        prev_->next_ = next_;
    }
    
    void changeNextPrevious() {
        next_->prev_ = prev_;
    }
    
    bool isValid() const {
        return signature_ == HEAP_SIGNATURE;
    }
    
    AllocHeader* next() {
        return next_;
    }
    
    void previous(AllocHeader* h) {
        prev_ = h;
    }
    
    AllocHeader* previous() {
        return prev_;
    }
    
    Heap* heap() {
        return heap_;
    }
    
    size_t size() const {
        return size_;
    }
    
    bool hasPrevious() const {
        return prev_ != nullptr;
    }
    
    bool hasNext() const {
        return next_ != nullptr;
    }
    
private:
    uint32_t signature_;
    size_t size_;
    Heap* heap_;
    AllocHeader* next_;
    AllocHeader* prev_;
    const char* file_name_;
    int line_;
};


Heap::Heap()
    : active_(false)
    , allocated_(0)
    , peak_(0)
    , instances_(0)
    , head_alloc_(nullptr)
    , first_child_(nullptr)
    , next_siblind_(nullptr)
    , prev_sibling_(nullptr)
{
    strcpy( heap_name_, "NonActiveHeap" );    
    T3_TRACE("heap ctor.\n");
}


void* Heap::allocate(const size_t size) {
    return allocate(size, nullptr, -1);
}


void* Heap::allocate(
    const size_t size,
    const char* const file_name,
    const int line
) {
    //  本当に確保するサイズ　リクエストサイズ + ヘッダ情報 + 終端マーク4byte
    size_t alloc_header_size = sizeof(AllocHeader);
    size_t request_bytes = size + alloc_header_size;

#if ALLOC_ENDMARKING
    request_bytes += sizeof(uint32_t);
#endif // ALLOC_ENDMARKING

    //  メモリ確保
    int8_t* mem = reinterpret_cast<int8_t*>(std::malloc(request_bytes));
    AllocHeader* header = reinterpret_cast< AllocHeader* >(mem);

    //  ヘッダ情報書き込み
    header->setup(
        size,
        this,
        head_alloc_,
        nullptr,
        file_name,
        line
    );

    if (head_alloc_) {
        head_alloc_->previous(header);
    }

    
    
    //  ヘッダリストの先頭を更新
    head_alloc_ = header;
    
    //  トータルの割り当てサイズ
    allocated_ += size;
    
    //  ピークサイズ判定
    if (allocated_ > peak_) {
        peak_ = allocated_;
    }
    
    instances_ += 1;

    void* start_mem_block = mem + alloc_header_size;

#if ALLOC_ENDMARKING
    uint32_t* end_mark = reinterpret_cast<uint32_t*>((intptr_t)start_mem_block + size);
    *end_mark = ALLOC_END_MARK;
#endif // ALLOC_ENDMARKING

#if DIRTY_MEMORY
    size_t alloc_size = size;
    std::memset(start_mem_block, DIRTY_ALLOC_MARK, alloc_size);
#endif

    return start_mem_block;
}


void Heap::deallocate(
    void* mem
) {
    if (!mem) {
        return;
    }

    AllocHeader* header = reinterpret_cast<AllocHeader*>(
        (reinterpret_cast<char*>(mem) - sizeof(AllocHeader))
    );
    T3_ASSERT(header->isValid());
 
#if ALLOC_ENDMARKING
    uint32_t* end_mark = reinterpret_cast<uint32_t*>((intptr_t)mem + header->size());
    T3_ASSERT(*end_mark == ALLOC_END_MARK);
#endif // ALLOC_ENDMARKING

  
    header->heap()->deallocate(header);
}


void Heap::deallocate(
    AllocHeader* header
) {
    if (header->hasPrevious()) {
        header->changePreviousNext();
    }
    else {
        head_alloc_ = header->next();
    }
    
    
    if (header->hasNext()) {
        header->changeNextPrevious();
    }
    
    allocated_ -= header->size();
    instances_ -= 1;


#if DIRTY_MEMORY
    size_t alloc_size = header->size() + sizeof(AllocHeader);
    std::memset(header, DIRTY_FREE_MARK, alloc_size);
#endif

    std::free(header);
}

void Heap::activate(const char *const name)
{
    T3_NULL_ASSERT(name);
    T3_ASSERT(strlen(name) < NAME_LENGTH);
    
    strcpy(heap_name_, name);
    allocated_ = 0;
    peak_ = 0;
    instances_ = 0;
    active_ = true;
}

void Heap::deactivate()
{
    strcpy(heap_name_, "");
    
    allocated_ = 0;
    peak_ = 0;
    instances_ = 0;
    active_ = false;
}





}   // namespace t3



