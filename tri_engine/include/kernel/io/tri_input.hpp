

#ifndef TRI_INPUT_HPP_INCLUDED
#define TRI_INPUT_HPP_INCLUDED

//  include
#include "tri_pad.hpp"
#include "tri_pointing.hpp"


namespace t3 {

///
/// ���͏��
class Input
    : private Uncopyable
{
public:
    ///
    /// �p�b�h���擾
    const Pad& pad() const {
        return pad_;
    }
    
    ///
    /// �|�C���e�B���O���擾
    const Pointing& pointing() const {
        return pointing_;
    }
    
    ///
    /// �����x�Z���T�[���擾
    const cross::AccelerometerData& getAccelerometer() const {
        return accele_;
    }


    ///
    /// �Q�[���p�b�h�����X�V
    void updatePad(
        const cross::GamePadData& paddata,
        tick_t delta_time
    ) {
        pad_.updatePad(paddata.buttonData(), delta_time);
    }
    
    ///
    /// �|�C���e�B���O�f�o�C�X�����X�V
    void updatePointing(
        const cross::PointingData& pointing_data,
        tick_t delta_time
    ) {
        pointing_.updatePointing(pointing_data, delta_time);
    }
    
    ///
    /// �����x�Z���T�[�����X�V
    void updateAccelermeter(
        const cross::AccelerometerData acc_data,
        tick_t delta_time
    ) {
        (void)delta_time;
        accele_ = acc_data;
    }

    
private:
    Pad pad_;                           ///< �Q�[���p�b�h���
    Pointing pointing_;                 ///< �|�C���e�B���O�f�o�C�X���
    cross::AccelerometerData accele_;   ///< �����x�Z���T�[
};
  

}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

