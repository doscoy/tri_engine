//  M系列乱数

#ifndef TRI_RANDOM_MSEQ_HPP_INCLUDED
#define TRI_RANDOM_MSEQ_HPP_INCLUDED

#include "../../tri_develop_base.hpp"


namespace t3 {

class RandomMseq {

public:
    //  コンストラクタ
	explicit RandomMseq( const u_int seed );

    //  デストラクタ
	~RandomMseq();

public:
    //  乱数取得
    u_int getUInt();


private:
    u_int seed_;
};



} // namespace t3


#endif // TRI_RANDOM_MSEQ_HPP_INCLUDED
