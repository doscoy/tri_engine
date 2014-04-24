
#ifndef TRI_RESOURCE_HPP_INCLUDED
#define TRI_RESOURCE_HPP_INCLUDED


#include "util/tri_uncopyable.hpp"
#include "util/tri_unique_id.hpp"
#include "kernel/tri_kernel.hpp"

#include <cstring>

constexpr int RESOURCE_NAME_SIZE = 200;

namespace t3 {
inline namespace base {


class Resource
    : private Uncopyable
{
public:
    Resource();
    virtual ~Resource(){}
    
public:
    void setResourceName(const char* const name){
        std::strncpy(
            resource_name_,
            name,
            RESOURCE_NAME_SIZE
        );
    }
    const char* getResourceName() const {
        return resource_name_;
    }
    
    UniqueID getResourceID() const {
        return resource_id_;
    }
    
private:
    UniqueID resource_id_;
    char resource_name_[RESOURCE_NAME_SIZE];
};

}   // namespace base
}   // namespace t3

#endif // TRI_RESOURCE_HPP_INCLUDED
