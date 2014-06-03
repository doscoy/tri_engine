
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
    Collider(
        const HashString& name
    );
    virtual ~Collider(){};
    
public:
    virtual bool isHit(const PointCollider& col) const {
        return false;
    }
    
    virtual bool isHit(const CircleCollider& col) const {
        return false;
    }

    virtual const HashString& getCollisionType() const = 0;

public:
    const UniqueID& getColliderID() const {
        return collider_id_;
    }
    
    const HashString& getColliderName() const {
        return collider_name_;
    }

public:
    bool operator ==(const Collider& rhs) {
        return getColliderID() == rhs.getColliderID();
    }

private:
    UniqueID collider_id_;
    HashString collider_name_;
};


using ColliderPtr = std::shared_ptr<Collider>;

        
}   // namaespace geometry
}   // namespace t3


#endif
