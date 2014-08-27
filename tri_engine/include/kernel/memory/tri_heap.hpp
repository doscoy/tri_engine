

#ifndef TRI_HEAP_HPP_INCLUDED
#define TRI_HEAP_HPP_INCLUDED

#include <cstddef>
#include "kernel/process/tri_mutex.hpp"
#include "util/tri_uncopyable.hpp"


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
    const char* name() const
    {
        return heap_name_;
    }

    void activate(const char* const name);
    void deactivate();

    bool isActive() const
    {
        return active_;
    }


    void* allocate(const size_t size);
    void* allocate(
        const size_t size,
        const char* const file_name,
        const int line
    );
    static void  deallocate(void* mem);

    void dump() const;
    void ASSERT_HEADER() const;
    void ASSERT_HEADER(AllocHeader* a) const;


    static Mutex& mutex()
    {
        return mutex_;
    }
private:
    void deallocate( AllocHeader* header );
    void getTreeStats( size_t& total_bytes, size_t& total_peak, int& total_instances ) const;

private:
    bool active_;
    char heap_name_[NAME_LENGTH];
    size_t allocated_;
    size_t peak_;
    int instances_;
    AllocHeader* head_alloc_;

    Heap* first_child_;
    Heap* next_siblind_;
    Heap* prev_sibling_;

    static Mutex mutex_;
};




}   // namespace t3


#endif // TRI_HEAP_HPP_INCLUDED
