////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_signature.hpp
    32bitシグネチャ生成.
*/

#ifndef TRI_SIGNATURE_HPP_INCLUDED
#define TRI_SIGNATURE_HPP_INCLUDED

#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


///
/// シグネチャ生成.
/// ex. TriEngineを識別するためのシグネチャ　"TriE"　を作成する
///   uint32_t sig = makeSignature('T', 'r', 'i', 'E');
inline constexpr uint32_t makeSignature(
    char a,
    char b,
    char c,
    char d
) {
    return ((a) | (b << 8) | (c << 16) | (d << 24));
}

TRI_CORE_NS_END


#endif  // TRI_SIGNATURE_HPP_INCLUDED
