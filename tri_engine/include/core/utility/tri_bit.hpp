////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_bit.hpp
    各種ビット操作関数.
*/

#ifndef TRI_BIT_HPP_INCLUDED
#define TRI_BIT_HPP_INCLUDED

// includes
#include "core/core_config.hpp"
#include "core/base/tri_std.hpp"

TRI_CORE_NS_BEGIN



///
/// 指定bitを立てる
inline void bitOn(
    uint32_t& v,
    const uint32_t bit
) {
    v |= bit;
}

///
/// 指定ビットを落とす
inline void bitOff(
    uint32_t& v,
    const uint32_t bit
) {
    v &= ~bit;
}

///
/// 指定ビット列がセットされた状態にする
inline void bitSet(
    uint32_t& v,
    const uint32_t bit
) {
    v = bit;
}

///
/// ビット列をクリア
inline void bitClear(
    uint32_t& v
) {
    v = 0;
}

///
/// 指定ビットが立っているか判定
inline bool bitCheck(
    const uint32_t v,
    const uint32_t bit
) {
    return (v & bit) == bit;
}

///
/// ビット可視化用文字列作成.
/// 0xf0 = "11110000"
const char* bitToString(
    const uint32_t v,           ///< 表示したいビット列
    const int bit_num =  32     ///< 下位何ビットを表示するか
);

///
/// 立っているビットを数える
uint32_t bitPopulation(const uint32_t bits);



TRI_CORE_NS_END


#endif // TRI_BIT_HPP_INCLUDED

