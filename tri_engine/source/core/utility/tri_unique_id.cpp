////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
#include "core/utility/tri_unique_id.hpp"

TRI_CORE_NS_BEGIN

//  新しいユニークIDのシード値
uint32_t UniqueID::uid_generator_ = 0;


UniqueID::UniqueID()
    : uid_(uid_generator_)
{
    //  インスタンスが作られるたびに新しい値が割り当てられる
    uid_generator_ += 1;
}




TRI_CORE_NS_END
