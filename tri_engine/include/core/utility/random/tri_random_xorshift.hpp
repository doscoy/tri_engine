////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_random_xorshift.hpp
    xorshift.
*/
#ifndef TRI_RANDOM_XORSHIFT_HPP_INCLUDED
#define TRI_RANDOM_XORSHIFT_HPP_INCLUDED

//  include
#include "core/base/tri_std.hpp"
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN



class RandomXorShift {


public:
    //  コンストラクタ
	RandomXorShift( const uint32_t seed );
	
    //  デストラクタ
	~RandomXorShift();



public:
    //  32bit乱数取得
	uint32_t getUInt();

	
private:
	uint32_t x_;
    uint32_t y_;
	uint32_t z_;
	uint32_t w_;
};


TRI_CORE_NS_END

#endif // TRI_RANDOM_XORSHIFT_HPP_INCLUDED
