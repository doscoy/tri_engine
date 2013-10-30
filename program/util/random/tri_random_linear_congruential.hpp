
#ifndef TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED
#define TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED


#include "../../tri_develop_base.hpp"


namespace t3 {


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


} // namespace t3


#endif // TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED
