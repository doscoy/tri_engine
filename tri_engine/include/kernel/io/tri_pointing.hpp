

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
        tick_t tick
    );
    
    bool isHold() const {
        return hold_;
    }
    
    bool isTrigger() const {
        return trigger_;
    }
    
    bool isDoubleClick() const {
        return double_click_;
    }
    
    bool isRelease() const {
        return release_;
    }

    const Point2& getPosition() const {
        return position_[0];
    }

    const Point2& getMoving() const {
        return moving_;
    }

private:
    void clearPositionList();

private:
    enum {
        MAX_POSITION_SIZE = 60,
    };

    bool hold_;
    bool trigger_;
    bool release_;
    bool double_click_;
    Point2 position_[MAX_POSITION_SIZE];
    Point2 moving_;
    float double_click_timer_;
    int double_click_release_count_;
};


}   // namespace kernel
}   // namespace t3

#endif // TRI_POINTING_HPP_INCLUDED

