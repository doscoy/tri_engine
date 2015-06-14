
#include "core/base/tri_resource.hpp"


TRI_CORE_NS_BEGIN



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

TRI_CORE_NS_END

