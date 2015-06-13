/**
    @file tri_random_mseq.hpp
    M系列乱数.
*/

#ifndef TRI_RANDOM_MSEQ_HPP_INCLUDED
#define TRI_RANDOM_MSEQ_HPP_INCLUDED

#include "base/tri_std.hpp"
#include "core_config.hpp"

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
