//  xorshift乱数

#ifndef TRI_RANDOM_XORSHIFT_HPP_INCLUDED
#define TRI_RANDOM_XORSHIFT_HPP_INCLUDED

#include "../../tri_develop_base.hpp"

namespace t3 {


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


} // namespace t3

#endif // TRI_RANDOM_XORSHIFT_HPP_INCLUDED
