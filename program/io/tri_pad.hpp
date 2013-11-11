

#ifndef TRI_PAD_HPP_INCLUDED
#define TRI_PAD_HPP_INCLUDED

#include "../tri_develop_base.hpp"
#include "../util/tri_uncopyable.hpp"

namespace t3 {
    

class Pad 
    : private Uncopyable
{
public:
    enum ButtonID{
        BUTTON_1     = 1 << 0,
        BUTTON_2     = 1 << 1,
        BUTTON_3     = 1 << 2,
        
        BUTTON_UP    = 1 << 5,
        BUTTON_DOWN  = 1 << 6,
        BUTTON_RIGHT = 1 << 7,
        BUTTON_LEFT  = 1 << 8,
        
        MAX_NORMAL_BUTTON_ID = 7,
        
        DEBUG_BUTTON_1 = 1 << 16,
        DEBUG_BUTTON_2 = 1 << 17,
        DEBUG_BUTTON_3 = 1 << 18,
        
        MAX_DEBUG_BUTTON_ID = 3,
        
        MAX_BUTTON_ID = MAX_NORMAL_BUTTON_ID + MAX_DEBUG_BUTTON_ID,
    };
    
public:
    Pad();
    ~Pad();

public:
    void updatePad( uint32_t current_frame_data, tick_t tick );
    
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
    void updateRepeat( tick_t tick );
    
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

