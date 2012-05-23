
#ifndef TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED
#define TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED


#include "../../tri_develop_base.hpp"


namespace t3 {


//	Linear congruential generators
class RandomLcgs {


public:
    //  コンストラクタ
	explicit RandomLcgs( const u_int seed );
	
    //  デストラクタ
	~RandomLcgs();


public:
    //  乱数取得
	u_int getUInt();
	u_short getUShort();	
	
private:
	u_int seed_;
};


} // namespace t3


#endif // TRI_RANDOM_LINEAR_CONGRUENTIAL_HPP_INCLUDED
