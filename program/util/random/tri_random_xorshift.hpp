//  xorshift乱数

#ifndef TRI_RANDOM_XORSHIFT_HPP_INCLUDED
#define TRI_RANDOM_XORSHIFT_HPP_INCLUDED

#include "../../tri_develop_base.hpp"

namespace t3 {


class RandomXorShift {


public:
    //  コンストラクタ
	RandomXorShift( const u_int seed );
	
    //  デストラクタ
	~RandomXorShift();



public:
    //  32bit乱数取得
	u_int getUInt();

	
private:
	u_int x_;
    u_int y_;
	u_int z_;
	u_int w_;
};


} // namespace t3

#endif // TRI_RANDOM_XORSHIFT_HPP_INCLUDED
