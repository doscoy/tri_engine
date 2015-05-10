

#ifndef TRI_INPUT_HPP_INCLUDED
#define TRI_INPUT_HPP_INCLUDED

//  include
#include "tri_pad.hpp"
#include "tri_pointing.hpp"


namespace t3 {

///
/// 入力情報
class Input
    : private Uncopyable
{
public:
    ///
    /// パッド情報取得
    const Pad& pad() const {
        return pad_;
    }
    
    ///
    /// ポインティング情報取得
    const Pointing& pointing() const {
        return pointing_;
    }
    
    ///
    /// 加速度センサー情報取得
    const cross::AccelerometerData& getAccelerometer() const {
        return accele_;
    }


    ///
    /// ゲームパッド情報を更新
    void updatePad(
        const cross::GamePadData& paddata,
        tick_t delta_time
    ) {
        pad_.updatePad(paddata.buttonData(), delta_time);
    }
    
    ///
    /// ポインティングデバイス情報を更新
    void updatePointing(
        const cross::PointingData& pointing_data,
        tick_t delta_time
    ) {
        pointing_.updatePointing(pointing_data, delta_time);
    }
    
    ///
    /// 加速度センサー情報を更新
    void updateAccelermeter(
        const cross::AccelerometerData acc_data,
        tick_t delta_time
    ) {
        (void)delta_time;
        accele_ = acc_data;
    }

    
private:
    Pad pad_;                           ///< ゲームパッド情報
    Pointing pointing_;                 ///< ポインティングデバイス情報
    cross::AccelerometerData accele_;   ///< 加速度センサー
};
  

}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

