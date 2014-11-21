#ifndef TRI_ARRAY_SIZE_HPP_INCLUDED
#define TRI_ARRAY_SIZE_HPP_INCLUDED

namespace t3 {

// *********************************************
//  配列の要素数取得テンプレート
//  int ar[123];  arraySize( ar ) => 123
template <typename Array, int N>
int arraySize1D( Array (&)[N] ) {
    return N;
}


template <typename Array, int N, int M>
void arraySize2D(Array (&)[N][M], int* x, int* y) {
    *x = M;
    *y = N;
}

    
}   // namespace t3

#endif // TRI_ARRAY_SIZE_HPP_INCLUDED