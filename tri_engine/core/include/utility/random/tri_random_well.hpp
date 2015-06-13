/**
    @file tri_random_well.hpp
    WELL乱数.
*/

#ifndef TRI_RANDOM_WELL_HPP_INCLUDED
#define TRI_RANDOM_WELL_HPP_INCLUDED

#include "core_config.hpp"
#include "base/tri_std.hpp"

TRI_CORE_NS_BEGIN



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

TRI_CORE_NS_END

#endif // TRI_RANDOM_WELL_HPP_INCLUDED
