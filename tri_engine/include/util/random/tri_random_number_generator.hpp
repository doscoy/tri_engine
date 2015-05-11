/**
    @file tri_random_number_generator.hpp
    乱数生成器インターフェース.
*/

#ifndef TRI_RANDOM_NUMBER_GENERATOR_HPP_INCLUDED
#define TRI_RANDOM_NUMBER_GENERATOR_HPP_INCLUDED


#include "../../util/tri_uncopyable.hpp"


namespace t3 {


///
/// 乱数生成器.
/// 実際の乱数生成の実装はテンプレートで渡す。
template<typename RandomAlgorithm>
class RandomNumberGenerator
    : private Uncopyable
{

public:

	explicit RandomNumberGenerator( const uint32_t seed )
        : algorithm_( seed )
    {
		// none
	}
	
	//  デストラクタ
    ~RandomNumberGenerator()
	{
		// none
	}
	

public:
    //  uint32_t
    uint32_t getUInt() {
        return algorithm_.getUInt();
    }
	
    //  uint32_t limit
    uint32_t getUInt(const uint32_t limit) {
        return (algorithm_.getUInt() % limit);
    }

    //  int
    int getInt() {
        return (int)getUInt(
            (uint32_t)std::numeric_limits<int>::max()
        );
    }

    //  int limit
    int getInt( const int limit ){
        return getInt() % limit;
    }
	
    //  bool 乱数取得 0 or 1
    bool getBool() {
        return (algorithm_.getUInt() & 2) == 0;
    }
	
    //  float 乱数取得 0.00f〜1.00f
    float getFloat() {
        return ((float)getUInt(std::numeric_limits<uint16_t>::max()) / (float)std::numeric_limits<uint16_t>::max());
    }
    
    //  float limit
    float getFloat(float limit){
        return getFloat() * limit;
    }

private:
    RandomAlgorithm algorithm_;

};


} // namespace t3

#endif // TRI_RANDOM_NUMBER_GENERATOR_HPP_INCLUDED
