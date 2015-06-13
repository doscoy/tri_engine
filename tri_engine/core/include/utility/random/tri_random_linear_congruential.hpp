/**
    @file tri_random_linear_congruential.hpp
    線形合同法.
*/

#ifndef TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED
#define TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED

#include "core_config.hpp"
#include "base/tri_std.hpp"

TRI_CORE_NS_BEGIN



//	Linear congruential generators
class RandomLcgs {


public:
    //  コンストラクタ
	explicit RandomLcgs( const uint32_t seed );
	
    //  デストラクタ
	~RandomLcgs();


public:
    //  乱数取得
	uint32_t getUInt();
	uint16_t getUShort();	
	
private:
	uint32_t seed_;
};

TRI_CORE_NS_END


#endif // TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED
