
#ifndef TRI_RESOURCE_HPP_INCLUDED
#define TRI_RESOURCE_HPP_INCLUDED


#include "util/tri_uncopyable.hpp"
#include "util/tri_unique_id.hpp"
#include "kernel/tri_kernel.hpp"



constexpr int RESOURCE_NAME_SIZE = 128;

namespace t3 {
inline namespace base {


class Resource
    : private Uncopyable
{
public:
    Resource();
    Resource(const char* const name);
    virtual ~Resource(){}
    
public:
    void resourceName(const char* const name){
        std::strncpy(
            resource_name_,
            name,
            RESOURCE_NAME_SIZE
        );
    }
    const char* resourceName() const {
        return resource_name_;
    }
    
    UniqueID resourceID() const {
        return resource_id_;
    }
    
private:
    UniqueID resource_id_;
    char resource_name_[RESOURCE_NAME_SIZE];
};

}   // namespace base
}   // namespace t3

#endif // TRI_RESOURCE_HPP_INCLUDED
