
#include "tri_resource.hpp"
#include "../util/tri_unique_id.hpp"


namespace t3 {

Resource::Resource()
    : id_(0)
    , name_{{0}}
{
    id_ = uniqueID();
}


}   //  namespace t3