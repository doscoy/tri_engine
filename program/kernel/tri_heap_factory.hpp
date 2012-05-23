
#ifndef TRI_HEAP_FACTORY_HPP_INCLUDED
#define TRI_HEAP_FACTORY_HPP_INCLUDED

#include "tri_heap.hpp"
#include <array>


namespace t3 {

class HeapFactory
{
public:
    static Heap* createHeap( const char* const name );
    static Heap* createHeap( const char* const name, const char* const parent );
    static void destroyHeap( Heap* heap );
    static Heap* getDefaultHeap();

private:
    static void initialize();
    static Heap* findHeap( const char* const name );
    static Heap* createNewHeap( const char* const name ); 
    static Heap* getRootHeap();

private:
    static Heap* root_heap_;
    static Heap* default_heap_;
    static std::array<Heap, 10> heaps_;
};


};

#endif // TRI_HEAP_FACTORY_HPP_INCLUDED

