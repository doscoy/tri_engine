
#include "tri_random_mseq.hpp"


namespace {

//	可能な組み合わせ(p,q) 
//	(2,1) (3,1) (4,1) (7,1) (17,3) (23,5) (31,3) (35,2) (41,20) (63,5) (65,32) (127,63) (255,82) (524,167) (756,19)

//
const t3::u_int FIX_P = 31;
const t3::u_int FIX_Q = 3;
const t3::u_int FIX_MASK = 0x7fffffff;

}	// unname namespace




namespace t3 {

RandomMseq::RandomMseq( const u_int seed )
    : seed_( seed )
{
	// none
}

RandomMseq::~RandomMseq()
{
	// none
}

u_int RandomMseq::getUInt()
{
	u_int s = seed_;
	u_int bit = ( ( s >> ( FIX_P -1) )  ^  ( s >> ( FIX_Q -1) ) ) & 1;
	seed_ = ( (s << 1) | bit ) & FIX_MASK;

	return ( seed_ );
}


} // namespace t3




