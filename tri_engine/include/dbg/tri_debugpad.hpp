#ifndef TRI_DEBUGPAD_HPP_INCLUDED
#define TRI_DEBUGPAD_HPP_INCLUDED

#include "../kernel/tri_kernel.hpp"

namespace t3 {


///
/// �f�o�b�O�p�b�h�擾
const Pad& debugPad();

///
/// �f�o�b�O�p�b�h�̍X�V
void updateDebugPad( 
    const uint32_t pad_data,    ///< �p�b�h�̓��͏��
    tick_t delta_time           ///< �`�b�N
);

}   // namespace t3





#endif // TRI_DEBUGPAD_HPP_INCLUDED