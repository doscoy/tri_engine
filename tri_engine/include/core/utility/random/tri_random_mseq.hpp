////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_random_mseq.hpp
    M系列乱数.
*/

#ifndef TRI_RANDOM_MSEQ_HPP_INCLUDED
#define TRI_RANDOM_MSEQ_HPP_INCLUDED

#include "core/base/tri_std.hpp"
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


class RandomMseq {

public:
    //  コンストラクタ
	explicit RandomMseq( const uint32_t seed );

    //  デストラクタ
	~RandomMseq();

public:
    //  乱数取得
    uint32_t getUInt();


private:
    uint32_t seed_;
};



TRI_CORE_NS_END


#endif // TRI_RANDOM_MSEQ_HPP_INCLUDED
