
#include "tri_resource.hpp"
#include "util/tri_unique_id.hpp"


namespace t3 {
inline namespace base {

Resource::Resource()
    : resource_id_(0)
    , resource_name_{"\0"}
{
    resource_id_ = uniqueID();
}

}   //  namespace base
}   //  namespace t3

