
#include "tri_random_well.hpp"

namespace t3 {


//  コンストラクタ
RandomWell::RandomWell( const u_int seed )
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
u_int RandomWell::getUInt()
{
	u_int idx = index_;

	u_int a = state_[idx];
	u_int c = state_[(idx+13) & 15];
	u_int b = a ^ c ^ (a<<16) ^ (c<<15);
	c = state_[( idx + 9 ) & 15];
	c ^= ( c >> 11 );
	a = state_[idx] = b ^ c;
	u_int d = a ^ ( (a << 5 ) & 0xDA442D20UL );
	idx = ( idx + 15 ) & 15;
	a = state_[idx];
	state_[idx] = a ^ b ^ d ^ ( a << 2 ) ^ ( b << 18 ) ^ ( c << 28 );

	index_ = idx;
	

	return ( state_[index_] );
		
}


} // namespace t3

