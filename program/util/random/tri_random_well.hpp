//  WELLアルゴリズム乱数

#ifndef TRI_RANDOM_WELL_HPP_INCLUDED
#define TRI_RANDOM_WELL_HPP_INCLUDED

#include "../../tri_develop_base.hpp"

namespace t3 {


class RandomWell {

public:
    //  コンストラクタ
	explicit RandomWell( const uint32_t seed );

    //  デストラクタ
	~RandomWell();

public:
    //  乱数取得
	uint32_t getUInt();


private:
	uint32_t state_[16];
	uint32_t index_;

};

} // namespace t3

#endif // TRI_RANDOM_WELL_HPP_INCLUDED
