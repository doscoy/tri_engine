

#ifndef TRI_INPUT_HPP_INCLUDED
#define TRI_INPUT_HPP_INCLUDED

#include "tri_pad.hpp"
#include "tri_pointing.hpp"


//#include <cross_sdk/cross_sdk.hpp>


namespace t3 {
inline namespace kernel {

class Input
    : private Uncopyable
{
public:
    const Pad& pad() const {
        return pad_;
    }
    
    const Pointing& pointing() const {
        return pointing_;
    }
    
    const cross::AccelerometerData& getAccelerometer() const {
        return accele_;
    }


    void updatePad(
        const cross::GamePadData& paddata,
        tick_t delta_time
    ) {
        pad_.updatePad(paddata.buttonData(), delta_time);
    }
    
    void updatePointing(
        const cross::PointingData& pointing_data,
        tick_t delta_time
    ) {
        pointing_.updatePointing(pointing_data, delta_time);
    }
    
    void updateAccelermeter(
        const cross::AccelerometerData acc_data,
        tick_t delta_time
    ) {
        (void)delta_time;
        accele_ = acc_data;
    }

    
private:
    Pad pad_;
    Pointing pointing_;
    cross::AccelerometerData accele_;
};
  
}   // namespace kernel
}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

