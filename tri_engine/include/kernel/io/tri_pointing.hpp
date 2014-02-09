

#ifndef TRI_POINTING_HPP_INCLUDED
#define TRI_POINTING_HPP_INCLUDED

#include "../../math/tri_math_types.hpp"

namespace t3 {
    
class Pointing{
public:
    Pointing();
    ~Pointing();

public:
    void updatePointing(
        const bool hit,
        const Point2& position
    );
    
    bool isHold() const {
        return hold_;
    }
    
    bool isTrigger() const {
        return trigger_;
    }
    
    bool isRelease() const {
        return release_;
    }

    const Point2& getPosition() const {
        return position_;
    }

private:
    bool hold_;
    bool trigger_;
    bool release_;
    Point2 position_;
    
};



}   // namespace t3

#endif // TRI_POINTING_HPP_INCLUDED

