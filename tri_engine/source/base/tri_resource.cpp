
#include "base/tri_resource.hpp"


namespace t3 {


Resource::Resource()
    : Resource("\0")
{
}


Resource::Resource(
    const char* const name
)   : resource_id_()
    , resource_name_()
{

    std::strncpy(resource_name_, name, RESOURCE_NAME_SIZE);
}

}   //  namespace t3

