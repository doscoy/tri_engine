
#include "tri_random_linear_congruential.hpp"

namespace {

const t3::u_int FIX_A = 214013L;
const t3::u_int FIX_B = 2531011L;


inline t3::u_int mixSeed( const t3::u_int seed ){
	//	Xn+1 = A x Xn + B
	return ( FIX_A * seed + FIX_B );
}

} // unname namespace



namespace t3 {

//  コンストラクタ
RandomLcgs::RandomLcgs( const u_int seed ) : seed_( seed )
{
	// none
}

//  デストラクタ  
RandomLcgs::~RandomLcgs()
{
	// none
}


u_int RandomLcgs::getUInt()
{
	u_int uval = getUShort() << 16;
	u_int lval = getUShort();
	return ( uval | lval );
}


u_short RandomLcgs::getUShort()
{
	seed_ = mixSeed( seed_ );
	return ( static_cast<unsigned short>( (seed_ >> 16) & 0xffff ) );
}


} // namespace t3





