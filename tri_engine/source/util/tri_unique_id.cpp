#include "util/tri_unique_id.hpp"

namespace t3 {



uint32_t UniqueID::uid_generator_ = 0;


UniqueID::UniqueID()
    : uid_(uid_generator_)
{
    uid_generator_ += 1;
}




}   // namespace t3
