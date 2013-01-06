

#ifndef TRI_PAD_HPP_INCLUDED
#define TRI_PAD_HPP_INCLUDED

#include "../tri_develop_base.hpp"
#include "../util/tri_uncopyable.hpp"

namespace t3 {
    

enum PadButtonID{
    PAD_BUTTON_1     = 1 << 0,
    PAD_BUTTON_2     = 1 << 1,
    PAD_BUTTON_3     = 1 << 2,
    
    PAD_BUTTON_UP    = 1 << 5,
    PAD_BUTTON_DOWN  = 1 << 6,
    PAD_BUTTON_RIGHT = 1 << 7,
    PAD_BUTTON_LEFT  = 1 << 8,
};

class Pad 
    : private Uncopyable{

public:
    Pad();
    ~Pad();

public:
    void updatePad( u_int current_frame_data );
    
    bool isTrigger( u_int button ) const{
        return ( trigger_ & button );
    }
    
    bool isPress( u_int button ) const{
        return ( (last_frame_data_ & button) == button );
    }
    
    bool isRelease( u_int button ) const{
        return ( release_ & button );
    }

    bool isRepeat( u_int button ) const{
        return ( repeat_ & button );
    }
    
    
    u_int getTriggerBits() const {
        return trigger_;
    }
    
    u_int getPressBits() const {
        return last_frame_data_;
    }
    
    u_int getReleaseBits() const {
        return release_;
    }
    
    u_int getRepeatBits() const {
        return repeat_;
    }
    
private:
    u_int last_frame_data_;
    u_int trigger_;
    u_int release_;
    u_int repeat_;
    float repeat_time_;
};
    
}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

