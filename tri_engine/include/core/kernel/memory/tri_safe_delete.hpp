/**
    @file tri_safe_delete.hpp
    型安全delete.
*/

#ifndef TRI_SAFE_DELETE_HPP_INCLUDED
#define TRI_SAFE_DELETE_HPP_INCLUDED

// ---------------------------------------------
//  include
#include "core/base/tri_types.hpp"
#include "tri_memory.hpp"
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN



///
/// オブジェクトをdeleteしポインタを無効にする.
template < class T >
inline void safeDelete(T*& p) {
    //  不完全な型のポインタをT3_DELETEしようとした時にコンパイルエラーにする
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void)sizeof(type_must_be_complete);

    //  T3_DELETE    
    delete p;
    p = nullptr;
}


///
/// 配列をdelete後にポインタを無効にする.
template < class T >
inline void safeDeleteArray(T*& p) {
    //  不完全な型のポインタをT3_DELETEしようとした時にコンパイルエラーにする
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void)sizeof(type_must_be_complete);

    // T3_DELETE array
    delete[] p;
    p = nullptr;
}


    
TRI_CORE_NS_END

#endif // TRI_SAFE_DELETE_HPP_INCLUDED

