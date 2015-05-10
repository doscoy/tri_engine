#ifndef TRI_DEBUGPAD_HPP_INCLUDED
#define TRI_DEBUGPAD_HPP_INCLUDED

#include "../kernel/tri_kernel.hpp"

namespace t3 {


///
/// デバッグパッド取得
const Pad& debugPad();

///
/// デバッグパッドの更新
void updateDebugPad( 
    const uint32_t pad_data,    ///< パッドの入力情報
    tick_t delta_time           ///< チック
);

}   // namespace t3





#endif // TRI_DEBUGPAD_HPP_INCLUDED