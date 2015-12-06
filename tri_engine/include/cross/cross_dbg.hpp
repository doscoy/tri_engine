////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross_dbg.hpp
    crossで使うデバッグ用の簡易機構.
*/
#ifndef CROSS_DBG_HPP_INCLUDED
#define CROSS_DBG_HPP_INCLUDED

#include "cross_config.hpp"
#include "cross_std.hpp"


CROSS_NS_BEGIN


///
/// ソフトウェアブレークポイント
void breakpoint();


///
/// ブレークポイント
#define CROSS_BREAKPOINT()      cross::breakpoint()

///
/// 強制停止
#define CROSS_PANIC()           do{CROSS_BREAKPOINT(); abort();}while(0)

///
/// アサート
#define CROSS_ASSERT(exp)       do{if(!(exp)) CROSS_PANIC();}while(0)



CROSS_NS_END

#endif  // CROSS_DBG_HPP_INCLUDED
