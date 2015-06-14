#include "core/utility/tri_unique_id.hpp"

TRI_CORE_NS_BEGIN




uint32_t UniqueID::uid_generator_ = 0;


UniqueID::UniqueID()
    : uid_(uid_generator_)
{
    uid_generator_ += 1;
}




TRI_CORE_NS_END
