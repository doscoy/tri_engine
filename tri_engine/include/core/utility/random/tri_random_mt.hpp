////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_random_mt.hpp
    メルセンヌ・ツイスタ.
*/

#ifndef TRI_RANDOM_MT_HPP_INCLUDED
#define TRI_RANDOM_MT_HPP_INCLUDED

#include "core/core_config.hpp"
#include "core/base/tri_std.hpp"


TRI_CORE_NS_BEGIN


class RandomMT {

public:
	explicit RandomMT( const uint32_t seed );
	
	~RandomMT();
	
public:
	uint32_t getUInt();
	
private:
	void nextState();


private:
	enum {
		MAX_WORK = 624,
	};
	uint32_t state_[MAX_WORK];
	int left_;
	uint32_t* next_;

};

TRI_CORE_NS_END


#endif // TRI_RANDOM_MT_HPP_INCLUDED
