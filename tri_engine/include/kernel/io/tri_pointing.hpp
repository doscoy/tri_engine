

#ifndef TRI_POINTING_HPP_INCLUDED
#define TRI_POINTING_HPP_INCLUDED

#include "../../math/tri_math_types.hpp"
#include "platform/platform_types.hpp"
#include "base/tri_types.hpp"

namespace t3 {
inline namespace kernel {
    

class Pointing{
public:
    Pointing();
    ~Pointing();

public:
    void updatePointing(
        const PointingData& data,
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

    const Point2& position() const {
        return position_[0];
    }

    const Point2& moveDistance() const {
        return moving_;
    }
    
    int getPointingCount() const {
        return pointing_count_;
    }

private:
    void clearPositionList();

    void updateRepeat(tick_t delta_time);

private:
    enum {
        MAX_POSITION_SIZE = 60,
    };

    bool hold_;
    bool trigger_;
    bool release_;
    bool repeat_;
    bool moved_;
    bool double_click_;
    Point2 position_[MAX_POSITION_SIZE];
    Point2 moving_;
    float double_click_timer_;
    int double_click_release_count_;
    float repeat_interval_;
    float pressed_time_;
    int pointing_count_;
};


}   // namespace kernel
}   // namespace t3

#endif // TRI_POINTING_HPP_INCLUDED

