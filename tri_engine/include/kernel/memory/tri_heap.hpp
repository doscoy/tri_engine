

#ifndef TRI_HEAP_HPP_INCLUDED
#define TRI_HEAP_HPP_INCLUDED

#include "cross_sdk.hpp"
#include "base/tri_std.hpp"
#include "kernel/process/tri_mutex.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_bytesize.hpp"
#include "tri_memory_pool.hpp"

namespace t3 {

#define NAME_LENGTH  6
extern MemoryPool* heapMemoryPool() CROSS_WEAK_SIMBOL;

struct AllocHeader;
class Heap
    : private Uncopyable
{
public:
    Heap();
    ~Heap() = default;

public:
    const char* name() const {
        return heap_name_;
    }
    
    int no() const {
        return heap_no_;
    }

    void activate(const char* const name, int no);
    void deactivate();

    bool isActive() const {
        return active_;
    }


    void* allocate(const size_t size);
    void* allocate(
        const size_t size,
        const char* const file_name,
        const int line
    );
    static void  deallocate(void* mem);

    void dump(
        uint32_t filter_min,
        uint32_t filter_max
    ) const;
    
    //  １度のメモリ割り当てピーク
    ByteSize peak() {
        return peak_;
    }
    
    //  トータルのメモリ割り当て量
    ByteSize allocated() {
        return allocated_;
    }
    
    uint32_t nodeCount() {
        return node_count_;
    }

    static Mutex& mutex() {
        return mutex_;
    }
    
private:
    void deallocate(AllocHeader* header);

private:
    bool active_;
    char heap_name_[NAME_LENGTH];
    int heap_no_;
    ByteSize allocated_;
    ByteSize peak_;
    uint32_t node_count_;
    AllocHeader* head_alloc_;

    Heap* first_child_;
    Heap* next_siblind_;
    Heap* prev_sibling_;

    static Mutex mutex_;
};




}   // namespace t3


#endif // TRI_HEAP_HPP_INCLUDED
