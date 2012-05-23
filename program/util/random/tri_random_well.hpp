//  WELLアルゴリズム乱数

#ifndef TRI_RANDOM_WELL_HPP_INCLUDED
#define TRI_RANDOM_WELL_HPP_INCLUDED

#include "../../tri_develop_base.hpp"

namespace t3 {


class RandomWell {

public:
    //  コンストラクタ
	explicit RandomWell( const u_int seed );

    //  デストラクタ
	~RandomWell();

public:
    //  乱数取得
	u_int getUInt();


private:
	u_int state_[16];
	u_int index_;

};

} // namespace t3

#endif // TRI_RANDOM_WELL_HPP_INCLUDED
