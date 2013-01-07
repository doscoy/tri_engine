

#ifndef TRI_POINTING_HPP_INCLUDED
#define TRI_POINTING_HPP_INCLUDED

#include "../tri_develop_base.hpp"
#include "../math/tri_math_types.hpp"

namespace t3 {
    
class Pointing{
public:
    Pointing();
    ~Pointing();

public:
    void updatePointing(
        const bool hit,
        const ivec2_t& position
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

    const ivec2_t& getPosition() const {
        return position_;
    }

private:
    bool hold_;
    bool trigger_;
    bool release_;
    ivec2_t position_;
    
};



}   // namespace t3

#endif // TRI_POINTING_HPP_INCLUDED

