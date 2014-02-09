/**
 *
 * bit操作ユーティリティ.
 *
 */

#include "tri_bit.hpp"


namespace t3 {


const char* bitToString(
    const uint32_t v,          // 表示したいビット列
    const int bit_num       // 下位何ビットを表示するか
){

    static char str[33];

    uint32_t check_bit = 0x1 << (bit_num-1);

    for ( int idx = 0; idx < bit_num; ++idx ){
        if ( bitCheck(v, check_bit) ){
            str[idx] = '1';
        }
        else {
            str[idx] = '0';
        }
        check_bit >>= 1;
    }

    //  null文字設定しておく
    str[bit_num] = '\0';

    return str;
}


uint32_t bitPopulation(
    const uint32_t   bits
){
    uint32_t   n = (bits & 0x55555555u) + ((bits >> 1) & 0x55555555u);
    n = (n & 0x33333333u) + ((n >> 2) & 0x33333333u);
    n = (n + (n >> 4)) & 0x0F0F0F0Fu;
    n = (n + (n >> 8)) & 0x00FF00FFu;
    return (n + (n >> 16)) & 0x0000FFFFu;
}


}   // namespace nd

