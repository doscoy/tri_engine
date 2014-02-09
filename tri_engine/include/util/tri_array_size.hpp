#ifndef TRI_ARRAY_SIZE_HPP_INCLUDED
#define TRI_ARRAY_SIZE_HPP_INCLUDED

namespace t3 {

// *********************************************
//  配列の要素数取得テンプレート
//  int ar[123];  arraySize( ar ) => 123
template <typename Array, int N>
int arraySize( Array (&)[N] ) {
    return N;
}
    
}   // namespace t3

#endif // TRI_ARRAY_SIZE_HPP_INCLUDED