
#ifndef TRI_COLLIDER_HPP_INCLUDED
#define TRI_COLLIDER_HPP_INCLUDED

#include "util/tri_hash_string.hpp"
#include "util/tri_unique_id.hpp"
#include "util/tri_any.hpp"
#include "base/tri_std.hpp"


namespace t3 {


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

    void owner(Any any) {
        owner_ = any;
    }
    
    Any& owner() {
        return owner_;
    }
    
    const Any& owner() const {
        return owner_;
    }


public:
    bool operator ==(const Collider& rhs) {
        return getColliderID() == rhs.getColliderID();
    }

private:
    UniqueID collider_id_;
    HashString collider_name_;
    Any owner_;
};


using ColliderPtr = SharedPtr<Collider>;

        

}   // namespace t3


#endif
