

#ifndef TRI_INPUT_HPP_INCLUDED
#define TRI_INPUT_HPP_INCLUDED

#include "tri_pad.hpp"
#include "tri_pointing.hpp"

namespace t3 {
inline namespace kernel {

class Input
    : private Uncopyable
{
public:
    Pad& getPad() {
        return pad_;
    }
    
    const Pad& getPad() const {
        return pad_;
    }
    
    Pointing& getPointing() {
        return pointing_;
    }
    
    const Pointing& getPointing() const {
        return pointing_;
    }
    
    const AccelerometerData& getAccelerometer() const {
        return accele_;
    }
    
private:
    Pad pad_;
    Pointing pointing_;
    AccelerometerData accele_;
};
  
}   // namespace kernel
}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

