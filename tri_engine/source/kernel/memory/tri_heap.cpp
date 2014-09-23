
#include "base/tri_types.hpp"
#include "kernel/memory/tri_heap.hpp"
#include "dbg/tri_assert.hpp"
#include "dbg/tri_trace.hpp"
#include "util/tri_util.hpp"
#include "util/tri_counter.hpp"

#define DIRTY_MEMORY        1
#define ALLOC_ENDMARKING    1



namespace {



const char* UNKNOWEN_FILE_NAME = "Unknown...";

constexpr uint32_t HEAP_SIGNATURE   = t3::makeSignature('H','E','A','P');
constexpr uint32_t ALLOC_END_MARK   = 0x99999999;
constexpr uint32_t DIRTY_ALLOC_MARK = 0xDEADBEEF;
constexpr uint32_t DIRTY_FREE_MARK  = 0xCAFEC0DE;


}   // unname namespace


namespace t3 {

Mutex Heap::mutex_;


class AllocHeader {
public:
    void setup(
        uint32_t size,
        Heap* heap,
        AllocHeader* next,
        AllocHeader* prev,
        const char* file,
        uint32_t line
    ) {

        signature_ = HEAP_SIGNATURE;
        size_ = size;
        heap_ = heap;
        next_ = next;
        prev_ = prev;
        file_name_ = file;
        line_ = line;
        
        alloc_no_ = frame_counter_.now();

    }
    
    uint32_t no() {
        return alloc_no_;
    }


    void changePreviousNext() {
        prev_->next_ = next_;
    }

    void changeNextPrevious() {
        next_->prev_ = prev_;
    }

    bool isValid() const {
        if (signature_ != HEAP_SIGNATURE) {
            return false;
        }
        else if (size_ == 0) {
            return false;
        }

        return true;
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

    void dump() const {
        T3_TRACE_TERMINAL("[%u]Size %dbyte :%s(%d)\n",alloc_no_, size_, file_name_, line_);
    }

public:
    uint32_t signature_;
    uint32_t alloc_no_;
    uint32_t size_;
    uint32_t line_;
    Heap* heap_;
    AllocHeader* next_;
    AllocHeader* prev_;
    const char* file_name_;

};


Heap::Heap()
    : active_(false)
    , allocated_()
    , peak_()
    , node_count_(0)
    , head_alloc_(nullptr)
    , first_child_(nullptr)
    , next_siblind_(nullptr)
    , prev_sibling_(nullptr)
{
    strcpy(heap_name_, "None");
}


void* Heap::allocate(const size_t size) {
    void* p = allocate(size, UNKNOWEN_FILE_NAME, 0);
    return p;
}


void* Heap::allocate(
    const size_t size,
    const char* const file_name,
    const int line
) {
    ScopedLock lock(Heap::mutex());

    T3_ASSERT(size > 0);

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
        head_alloc_, // next
        nullptr,     // prev
        file_name,
        line
    );
    T3_ASSERT(header->next_ == head_alloc_);
    T3_ASSERT(header->prev_ == nullptr);

    if (head_alloc_) {
        //  headerを新しいhead_alloc_にする為
        //  既存のhead_alloc_の前はheaderになる
        head_alloc_->previous(header);
    }



    //  ヘッダリストの先頭を更新
    AllocHeader* last_head = head_alloc_;
    head_alloc_ = header;


    T3_ASSERT(head_alloc_->prev_ == nullptr);
    T3_ASSERT(head_alloc_->next_ == last_head);

    //  トータルの割り当てサイズ
    allocated_.add(size);

    //  ピークサイズ判定
    if (allocated_.byte() > peak_.byte()) {
        peak_.byte(allocated_.byte());
    }

    node_count_ += 1;

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

    ScopedLock lock(Heap::mutex());

    AllocHeader* header = reinterpret_cast<AllocHeader*>(
        (reinterpret_cast<char*>(mem) - sizeof(AllocHeader))
                          );
    T3_ASSERT(header->isValid());

#if ALLOC_ENDMARKING
    uint32_t* end_mark = reinterpret_cast<uint32_t*>((intptr_t)mem + header->size());
    T3_ASSERT(*end_mark == ALLOC_END_MARK);
#endif // ALLOC_ENDMARKING

    Heap* owner = header->heap();
    owner->deallocate(header);
}


void Heap::deallocate(
    AllocHeader* header
)
{

    if (header->hasPrevious()) {
        //  前の要素がある場合は前のリストのつなぎ先を次に変える
        header->changePreviousNext();
    } else {
        //  前が無い＝ヘッドなので次の要素をヘッドにする
        head_alloc_ = header->next();
    }


    if (header->hasNext()) {
        //  次がある場合、次の要素の前方つなぎ先を変更
        header->changeNextPrevious();
    }

    AllocHeader* prev = header->prev_;
    AllocHeader* next = header->next_;
    if (prev) {
        T3_ASSERT(prev->next_ == next);
    }

    if (next) {
        T3_ASSERT(next->prev_ == prev);
    }

    allocated_.sub(header->size());
    node_count_ -= 1;


#if DIRTY_MEMORY
    size_t alloc_size = header->size() + sizeof(AllocHeader);
    void* start_mem_block = header;
    std::memset(start_mem_block, DIRTY_FREE_MARK, alloc_size);
#endif

    std::free(header);
}

void Heap::activate(const char *const name, int no) {
    T3_NULL_ASSERT(name);
    T3_ASSERT(strlen(name) < NAME_LENGTH);

    strcpy(heap_name_, name);
    heap_no_ = no;
    active_ = true;
}

void Heap::deactivate() {
    strcpy(heap_name_, "");

    allocated_.byte(0);
    peak_.byte(0);
    node_count_ = 0;
    active_ = false;
}


void Heap::dump(
    const uint32_t filter_min,
    const uint32_t filter_max
) const {
    ScopedLock lock(Heap::mutex());

    AllocHeader* ah = head_alloc_;
    while (ah) {
        T3_ASSERT(ah->isValid());
        if (ah->no() > filter_min && filter_max > ah->no()) {
            ah->dump();
        }
        ah = ah->next();
    }

}



}   // namespace t3



