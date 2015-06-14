
#include "core/utility/random/tri_random_well.hpp"

TRI_CORE_NS_BEGIN



//  コンストラクタ
RandomWell::RandomWell( const uint32_t seed )
    : index_( 0 )
{

	state_[0] = seed;
	state_[1] = 1;
	state_[2] = 2;
	state_[3] = 3;
	state_[4] = 4;
	state_[5] = 5;
	state_[6] = 6;
	state_[7] = 7;
	state_[8] = 8;
	state_[9] = 9;
	state_[10] = 10;
	state_[11] = 11;
	state_[12] = 12;
	state_[13] = 13;
	state_[14] = 14;
	state_[15] = 15;
}

//  デストラクタ
RandomWell::~RandomWell()
{
}

//  乱数取得
uint32_t RandomWell::getUInt()
{
	uint32_t idx = index_;

	uint32_t a = state_[idx];
	uint32_t c = state_[(idx+13) & 15];
	uint32_t b = a ^ c ^ (a<<16) ^ (c<<15);
	c = state_[( idx + 9 ) & 15];
	c ^= ( c >> 11 );
	a = state_[idx] = b ^ c;
	uint32_t d = a ^ ( (a << 5 ) & 0xDA442D20UL );
	idx = ( idx + 15 ) & 15;
	a = state_[idx];
	state_[idx] = a ^ b ^ d ^ ( a << 2 ) ^ ( b << 18 ) ^ ( c << 28 );

	index_ = idx;
	

	return ( state_[index_] );
		
}


TRI_CORE_NS_END
