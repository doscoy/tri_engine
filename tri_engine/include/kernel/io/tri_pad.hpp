

#ifndef TRI_PAD_HPP_INCLUDED
#define TRI_PAD_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "base/tri_std.hpp"
#include "base/tri_types.hpp"

namespace t3 {


class Pad 
    : private Uncopyable
{
public:
    enum ButtonID{
        BUTTON_A        = 1 << 0,
        BUTTON_B        = 1 << 1,
        BUTTON_X        = 1 << 2,
        BUTTON_Y        = 1 << 3,
        
        BUTTON_L        = 1 << 5,
        BUTTON_R        = 1 << 6,
        
        BUTTON_UP       = 1 << 10,
        BUTTON_DOWN     = 1 << 11,
        BUTTON_RIGHT    = 1 << 12,
        BUTTON_LEFT     = 1 << 13,
        
        BUTTON_OPTION1  = 1 << 15,
        BUTTON_OPTION2  = 1 << 16,
        BUTTON_HOME     = 1 << 17,
        
        MAX_NORMAL_BUTTON_ID = 13,
        
        DEBUG_BUTTON_1  = 1 << 22,
        DEBUG_BUTTON_2  = 1 << 23,
        DEBUG_BUTTON_3  = 1 << 24,
        
        MAX_DEBUG_BUTTON_ID = 3,
        
        MAX_BUTTON_ID = MAX_NORMAL_BUTTON_ID + MAX_DEBUG_BUTTON_ID,
    };
    
public:
    Pad();
    ~Pad();

public:
    void updatePad( uint32_t current_frame_data, tick_t delta_time );
    
    bool isTrigger( uint32_t button ) const {
        return ( trigger_ & button );
    }
    
    bool isPress( uint32_t button ) const {
        return ( (last_frame_data_ & button) == button );
    }
    
    bool isRelease( uint32_t button ) const {
        return ( release_ & button );
    }

    bool isRepeat( uint32_t button ) const {
        return ( repeat_ & button );
    }
    
    
    uint32_t getTriggerBits() const {
        return trigger_;
    }
    
    uint32_t getPressBits() const {
        return last_frame_data_;
    }
    
    uint32_t getReleaseBits() const {
        return release_;
    }
    
    uint32_t getRepeatBits() const {
        return repeat_;
    }

private:
    void updateRepeat( tick_t delta_time );
    
private:
    uint32_t last_frame_data_;
    uint32_t trigger_;
    uint32_t release_;
    uint32_t repeat_;
    float repeat_start_time_;
    float repeat_interval_;
    float pressed_time_;
};
  

}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

