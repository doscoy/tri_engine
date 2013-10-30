
#include "tri_random_mseq.hpp"


namespace {

//	可能な組み合わせ(p,q) 
//	(2,1) (3,1) (4,1) (7,1) (17,3) (23,5) (31,3) (35,2) (41,20) (63,5) (65,32) (127,63) (255,82) (524,167) (756,19)

//
const uint32_t FIX_P = 31;
const uint32_t FIX_Q = 3;
const uint32_t FIX_MASK = 0x7fffffff;

}	// unname namespace




namespace t3 {

RandomMseq::RandomMseq( const uint32_t seed )
    : seed_( seed )
{
	// none
}

RandomMseq::~RandomMseq()
{
	// none
}

uint32_t RandomMseq::getUInt()
{
	uint32_t s = seed_;
	uint32_t bit = ( ( s >> ( FIX_P -1) )  ^  ( s >> ( FIX_Q -1) ) ) & 1;
	seed_ = ( (s << 1) | bit ) & FIX_MASK;

	return ( seed_ );
}


} // namespace t3




