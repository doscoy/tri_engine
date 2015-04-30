#ifndef TRI_NAMEABLE_HPP_INCLUDED
#define TRI_NAMEABLE_HPP_INCLUDED


#include "tri_hash_string.hpp"

namespace t3 {



class Nameable {
public:
    Nameable()
        : name_()
    {
    }
    
    Nameable(const String& name)
        : name_(name)
    {
    }
    
    virtual ~Nameable(){}
    
public:
    String name() const {
        return name_.string();
    }
    
    t3::HashString::key_t getNameHash() {
        return name_.key();
    }

    void name(const String name) {
        name_.setString(name);
    }

private:
    t3::HashString name_;
};

}   // namespace t3


#endif  //  TRI_NAMEABLE_HPP_INCLUDED

