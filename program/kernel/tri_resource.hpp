
#ifndef TRI_RESOURCE_HPP_INCLUDED
#define TRI_RESOURCE_HPP_INCLUDED


#include "../util/tri_uncopyable.hpp"
#include "../io/tri_file.hpp"
#include "tri_develop_base.hpp"
#include "cstring"

#define RESOURCE_NAME_SIZE  (32)

namespace t3 {

class Resource
    : private Uncopyable
{
public:
    Resource();
    virtual ~Resource(){}
    
public:
    virtual const byte* getData() const = 0;


    void setName( const char* const name ){
        std::strncpy( name_, name, RESOURCE_NAME_SIZE );
    }
    const char* getName() const {
        return name_;
    }
    
    u_int getResourceID() const {
        return id_;
    }
    
private:
    u_int id_;
    char name_[RESOURCE_NAME_SIZE];
};


}   // namespace t3

#endif // TRI_RESOURCE_HPP_INCLUDED
