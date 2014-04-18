
#ifndef TRI_COLLIDER_HPP_INCLUDED
#define TRI_COLLIDER_HPP_INCLUDED

#include "util/tri_hash_string.hpp"
#include "util/tri_unique_id.hpp"
#include <cstdint>


namespace t3 {
inline namespace geometry {

class PointCollider;
class CircleCollider;

class Collider {

public:
    Collider();
    virtual ~Collider(){};
    
public:
    virtual bool isHit(const PointCollider& col) const {
        return false;
    }
    
    virtual bool isHit(const CircleCollider& col) const {
        return false;
    }

    virtual const HashString& getType() const = 0;
    
public:
    const UniqueID& getColliderID() const {
        return collider_id_;
    }
    
    bool isJudged() const {
        return judged_;
    }
    
    void setJudged(
        const bool judged
    ) {
        judged_ = judged;
    }
    
    
private:
    UniqueID collider_id_;
    bool judged_;
};


        
}   // namaespace geometry
}   // namespace t3


#endif
