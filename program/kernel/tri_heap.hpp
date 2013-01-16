

#ifndef TRI_HEAP_HPP_INCLUDED
#define TRI_HEAP_HPP_INCLUDED

#include <cstddef>
#include "util/tri_uncopyable.hpp"

namespace t3 {

constexpr int HEAP_SIGNATURE = 0xDEADC0DE;
//constexpr int HEAP_ENDMARKER = 0x19830125;
constexpr int NAME_LENGTH = 32;


struct AllocHeader;
class Heap : private Uncopyable
{
public:
    Heap();
    ~Heap() = default;
    
public:
    const char* getName() const {
        return heap_name_;
    }
    
    void activate( const char* const name );
    void deactivate();
    
    bool isActive() const {
        return active_;
    }
    
    
    void attach( Heap* parent );
    
    void* allocate( size_t size );
    static void  deallocate( void* mem );
    
 
    
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


    Heap* parent_;
    Heap* first_child_;
    Heap* next_siblind_;
    Heap* prev_sibling_;


    static int next_alloc_number_;
};




}   // namespace t3


#endif // TRI_HEAP_HPP_INCLUDED
