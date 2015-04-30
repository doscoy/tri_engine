/**
 *
 * bit操作ユーティリティ.
 *
 */

#ifndef TRI_BIT_HPP_INCLUDED
#define TRI_BIT_HPP_INCLUDED


#include "base/tri_std.hpp"

namespace t3 {



// 指定bitを立てる
inline void bitOn(
    uint32_t& v,
    const uint32_t bit
) {
    v |= bit;
}

// 指定ビットを落とす
inline void bitOff(
    uint32_t& v,
    const uint32_t bit
) {
    v &= ~bit;
}

// 指定ビット列がセットされた状態にする
inline void bitSet(
    uint32_t& v,
    const uint32_t bit
) {
    v = bit;
}

// ビット列をクリア
inline void bitClear(
    uint32_t& v
) {
    v = 0;
}

// 指定ビットが立っているか判定
inline bool bitCheck(
    const uint32_t v,
    const uint32_t bit
) {
    return (v & bit) == bit;
}

// ビット可視化用文字列作成
const char* bitToString(
    const uint32_t v,          ///< 表示したいビット列
    const int bit_num =  32 ///< 下位何ビットを表示するか
);

//  1のビットを数える
uint32_t bitPopulation(const uint32_t bits);



} // namespace t3


#endif // TRI_BIT_HPP_INCLUDED

