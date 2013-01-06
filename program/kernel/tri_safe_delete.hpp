

#ifndef TRI_STD_HPP_INCLUDED
#define TRI_STD_HPP_INCLUDED

// ---------------------------------------------
//  include
#include "tri_types.hpp"
#include "tri_memory.hpp"

//==============================================================================
namespace t3 {


// *********************************************
// オブジェクトをdeleteしポインタを無効にする.
template < class T >
inline void safeDelete(T*& p) {
    //  不完全な型のポインタをdeleteしようとした時にコンパイルエラーにする
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void)sizeof(type_must_be_complete);

    //  delete    
    delete p;
    p = nullptr;
}


// *********************************************
// 配列をdelete後にポインタを無効にする.
template < class T >
inline void safeDeleteArray(T*& p) {
    //  不完全な型のポインタをdeleteしようとした時にコンパイルエラーにする
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void)sizeof(type_must_be_complete);

    // delete array
    delete[] p;
    p = nullptr;
}


    
} // namespace t3

#endif // TRI_ENGINE_HPP_INCLUDED

