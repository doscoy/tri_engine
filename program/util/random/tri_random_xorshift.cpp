
#include "tri_random_xorshift.hpp"

namespace t3 {

//  コンストラクタ
RandomXorShift::RandomXorShift( const u_int seed )
    : x_( 123456789 )
    , y_( 362436069 )
    , z_( 521288629 )
    , w_( 88675123 )
{	
	int loop_num = seed & 0xff;
	for ( int i = 0; i < loop_num; ++i ){
		getUInt();
	} 
}

//  デストラクタ
RandomXorShift::~RandomXorShift()
{
	// none
}

//  32bit乱数取得
u_int RandomXorShift::getUInt()
{
	unsigned long t = x_ ^ ( x_ << 11 );
	x_ = y_;
	y_ = z_;
	z_ = w_;
	w_ = static_cast<u_int>(( w_ ^ ( w_ >> 19 ) )  ^  ( t ^ ( t >> 8 ) ));
	
	return ( w_ );
}	




} // namespace t3

