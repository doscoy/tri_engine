////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "cross/cross_config.hpp"

CROSS_NS_BEGIN

///
/// ソフトウェアブレークポイント
void breakpoint() {
    //  デバッガ起動中ならトラップする
    __asm int 3;
}

CROSS_NS_END