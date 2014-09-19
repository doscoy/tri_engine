

#ifndef TRI_HEAP_HPP_INCLUDED
#define TRI_HEAP_HPP_INCLUDED

#include "base/tri_std.hpp"
#include "kernel/process/tri_mutex.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_bytesize.hpp"

namespace t3 {

constexpr int NAME_LENGTH = 6;


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

    void activate(const char* const name);
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

    void dump(uint32_t filter_min) const;
    
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
    
    static uint32_t allocateCount();
    
    
private:
    void deallocate(AllocHeader* header);

private:
    bool active_;
    char heap_name_[NAME_LENGTH];
    ByteSize allocated_;
    ByteSize peak_;
    uint32_t node_count_;
    AllocHeader* head_alloc_;

    Heap* first_child_;
    Heap* next_siblind_;
    Heap* prev_sibling_;

    static Mutex mutex_;
    static uint32_t alloc_count_;
};




}   // namespace t3


#endif // TRI_HEAP_HPP_INCLUDED
