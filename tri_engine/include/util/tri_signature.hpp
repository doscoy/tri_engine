/**
    @file tri_signature.hpp
    シグネチャ生成.
*/

#ifndef TRI_SIGNATURE_HPP_INCLUDED
#define TRI_SIGNATURE_HPP_INCLUDED

namespace t3 {

///
/// シグネチャ生成
inline constexpr uint32_t makeSignature(
    char a,
    char b,
    char c,
    char d
) {
    return ((a) | (b << 8) | (c << 16) | (d << 24));
}


}   // t3


#endif  // TRI_SIGNATURE_HPP_INCLUDED
