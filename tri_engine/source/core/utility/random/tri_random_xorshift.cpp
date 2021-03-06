////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/utility/random/tri_random_xorshift.hpp"

TRI_CORE_NS_BEGIN

//  コンストラクタ
RandomXorShift::RandomXorShift( const uint32_t seed )
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
uint32_t RandomXorShift::getUInt()
{
	unsigned long t = x_ ^ ( x_ << 11 );
	x_ = y_;
	y_ = z_;
	z_ = w_;
	w_ = static_cast<uint32_t>(( w_ ^ ( w_ >> 19 ) )  ^  ( t ^ ( t >> 8 ) ));
	
	return ( w_ );
}	



TRI_CORE_NS_END

