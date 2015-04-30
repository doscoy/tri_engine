#ifndef TRI_UNIQUE_ID_HPP_INCLUDED
#define TRI_UNIQUE_ID_HPP_INCLUDED

#include "base/tri_std.hpp"
#include "tri_uncopyable.hpp"


namespace t3 {



class UniqueID
{
public:
    UniqueID();

public:
    bool operator ==(const UniqueID& rhs) const {
        return uid_ == rhs.uid_;
    }
    
    bool operator !=(const UniqueID& rhs) const {
        return uid_ != rhs.uid_;
    }
    
    bool operator >(const UniqueID& rhs) const {
        return uid_ > rhs.uid_;
    }

    bool operator <(const UniqueID& rhs) const {
        return uid_ < rhs.uid_;
    }

    bool operator <=(const UniqueID& rhs) const {
        return uid_ <= rhs.uid_;
    }
    
    bool operator >=(const UniqueID& rhs) const {
        return uid_ >= rhs.uid_;
    }
    
private:
    uint32_t uid_;
    static uint32_t uid_generator_;
};



}   // namespace t3

#endif // TRI_UNIQUE_ID_HPP_INCLUDED
