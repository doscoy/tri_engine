
#include "tri_random_linear_congruential.hpp"

namespace {

const uint32_t FIX_A = 214013L;
const uint32_t FIX_B = 2531011L;


inline uint32_t mixSeed( const uint32_t seed ){
	//	Xn+1 = A x Xn + B
	return ( FIX_A * seed + FIX_B );
}

} // unname namespace



namespace t3 {

//  コンストラクタ
RandomLcgs::RandomLcgs( const uint32_t seed ) : seed_( seed )
{
	// none
}

//  デストラクタ  
RandomLcgs::~RandomLcgs()
{
	// none
}


uint32_t RandomLcgs::getUInt()
{
	uint32_t uval = getUShort() << 16;
	uint32_t lval = getUShort();
	return ( uval | lval );
}


uint16_t RandomLcgs::getUShort()
{
	seed_ = mixSeed( seed_ );
	return ( static_cast<uint16_t>( (seed_ >> 16) & 0xffff ) );
}


} // namespace t3





