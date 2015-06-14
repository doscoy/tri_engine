/**
    @file tri_new.hpp
    newオーバーライド.
*/

#ifndef TRI_NEW_HPP_INCLUDED
#define TRI_NEW_HPP_INCLUDED

//  include
#include <cstddef>
#include "core/kernel/memory/tri_heap_manager.hpp"



//#define T3_NEW          new(t3::HeapManager::getHeap(::t3::HEAP_APP) ,__FILE__, (int)__LINE__)
//#define T3_SYS_NEW      new(t3::HeapManager::getHeap(::t3::HEAP_SYS) ,__FILE__, (int)__LINE__)
//#define T3_DELETE       delete
//#define T3_DELETE_A     delete[]

#define T3_NEW      new
#define T3_SYS_NEW  new
#define T3_DELETE   delete
#define T3_DELETE_A delete[]

///
/// new
extern void* operator new(
    ::std::size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
);

///
/// delete
extern void operator delete(
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
);

///
/// 配列のnew
extern void* operator new[](
    ::std::size_t size,
    t3::Heap* heap,
    const char* const filename,
    int line
);

///
/// 配列のdelete
extern void operator delete[](
    void* mem,
    t3::Heap* heap,
    const char* const filename,
    int line
);



#endif // TRI_NEW_HPP_INCLUDED