////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_memory.hpp
    メモリ統合ヘッダ.
*/

#ifndef TRI_MEMORY_HPP_INCLUDED
#define TRI_MEMORY_HPP_INCLUDED

//  include
#include "tri_heap_manager.hpp"
#include "tri_heap.hpp"
#include "tri_heap_manager.hpp"
#include "tri_memory_pool.hpp"
#include "tri_new.hpp"
#include "tri_safe_delete.hpp"


///
/// メモリ確保
//#define T3_ALLOC(size)      ::t3::HeapManager::getHeap(::t3::HEAP_APP)->allocate(size, __FILE__, __LINE__)
#define T3_ALLOC(size)      std::malloc((size))

///
/// システムメモリ確保
//#define T3_SYS_ALLOC(size)  ::t3::HeapManager::getHeap(::t3::HEAP_SYS)->allocate(size, __FILE__, __LINE__)
#define T3_SYS_ALLOC(size)  std::malloc((size))

///
/// メモリ解放
//#define T3_FREE(addr)       ::t3::Heap::deallocate(addr)
#define T3_FREE(addr)       std::free((addr))


#endif // TRI_MEMORY_HPP_INCLUDED