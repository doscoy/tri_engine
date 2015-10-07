////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file tri_debugpad.hpp
    デバッグパッド.
*/

#ifndef TRI_DEBUGPAD_HPP_INCLUDED
#define TRI_DEBUGPAD_HPP_INCLUDED

#include "core/core_config.hpp"
#include "../kernel/tri_kernel.hpp"

TRI_CORE_NS_BEGIN

///
/// デバッグパッド取得
const Pad& debugPad();

///
/// デバッグパッドの更新
void updateDebugPad( 
    const cross::GamePadData& pad_data,    ///< パッドの入力情報
    DeltaTime delta_time           ///< チック
);

TRI_CORE_NS_END


#endif // TRI_DEBUGPAD_HPP_INCLUDED