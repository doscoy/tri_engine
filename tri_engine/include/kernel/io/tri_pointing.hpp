

#ifndef TRI_POINTING_HPP_INCLUDED
#define TRI_POINTING_HPP_INCLUDED

#include "../../math/tri_math_types.hpp"
#include "base/tri_types.hpp"

#include <cross_sdk/cross_sdk.hpp>

namespace t3 {
inline namespace kernel {
    

class Pointing{
public:
    Pointing();
    ~Pointing();

    enum class FlickDirection {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

public:
    void updatePointing(
        const cross::PointingData& data,
        tick_t delta_time
    );
    
    bool isHold() const {
        return hold_;
    }
    
    bool isTrigger() const {
        return trigger_;
    }
    
    bool isRepeat() const {
        return repeat_;
    }
    
    bool isDoubleClick() const {
        return double_click_;
    }
    
    bool isRelease() const {
        return release_;
    }
    
    bool isMoving() const {
        return moved_;
    }

    const Vec2& position() const {
        return position_[0];
    }

    const Vec2& moveDistance() const {
        return moving_;
    }
    
    int getPointingCount() const {
        return pointing_count_;
    }
    
    bool isFlick() const {
        return flick_;
    }
    
    const Vec2& flickMoveOffset() const {
    
        return flick_move_;
    }
    
    FlickDirection flickDirection() const {
        return flick_direction_;
    }
    
    

private:
    void clearPositionList();
    void updateFlick();
    void updateRepeat(tick_t delta_time);
    void updateMoving();

private:
    enum {
        MAX_POSITION_SIZE = 60,
    };

    bool hold_;
    bool trigger_;
    bool release_;
    bool repeat_;
    bool moved_;
    bool flick_;
    bool double_click_;
    Vec2 position_[MAX_POSITION_SIZE];
    Vec2 moving_;
    float double_click_timer_;
    int double_click_release_count_;
    float repeat_interval_;
    float pressed_time_;
    int pointing_count_;
    Vec2 trigged_position_;
    Vec2 released_position_;
    Vec2 flick_move_;
    FlickDirection flick_direction_;
};


}   // namespace kernel
}   // namespace t3

#endif // TRI_POINTING_HPP_INCLUDED

