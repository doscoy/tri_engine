

#ifndef TRI_HEAP_HPP_INCLUDED
#define TRI_HEAP_HPP_INCLUDED

#include <cstddef>
#include "kernel/process/tri_mutex.hpp"
#include "util/tri_uncopyable.hpp"
#include "util/tri_bytesize.hpp"

namespace t3 {

constexpr int NAME_LENGTH = 32;


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
    
    

    static Mutex& mutex() {
        return mutex_;
    }
    
    static uint32_t allocateCount();
    
    
private:
    void deallocate(AllocHeader* header);
    void getTreeStats(
        size_t& total_bytes,
        size_t& total_peak,
        int& total_instances
    ) const;

private:
    bool active_;
    char heap_name_[NAME_LENGTH];
    ByteSize allocated_;
    ByteSize peak_;
    int instances_;
    AllocHeader* head_alloc_;

    Heap* first_child_;
    Heap* next_siblind_;
    Heap* prev_sibling_;

    static Mutex mutex_;
    static uint32_t alloc_count_;
};




}   // namespace t3


#endif // TRI_HEAP_HPP_INCLUDED
