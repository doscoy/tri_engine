//  乱数取得インターフェイス

#ifndef TRI_RANDOM_NUMBER_GENERATOR_HPP_INCLUDED
#define TRI_RANDOM_NUMBER_GENERATOR_HPP_INCLUDED


#include "../../tri_develop_base.hpp"
#include "../../util/tri_uncopyable.hpp"


namespace t3 {


template<typename RandomAlgorithm>
class RandomNumberGenerator
    : Uncopyable
{

public:

	explicit RandomNumberGenerator( const u_int seed )
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
    //  unsigned int
    u_int getUInt() {
        return ( algorithm_.getUInt() );
    }
	
    //  unsigned int limit
    u_int getUInt( const u_int limit ) {
        return ( algorithm_.getUInt() % limit );	
    }

    //  int
    int getInt() {
        return ( static_cast<int>( algorithm_.getUInt() ) );
    }

    //  int limit
    int getInt( const int limit ){
        return ( getInt() % limit );
    }
	
    //  bool 乱数取得 0 or 1
    bool getBool() {
        return ( ( algorithm_.getUInt() & 2 ) == 0 );
    }
	
    //  float 乱数取得 0.00f〜1.00f
    float getFloat() {
        return ( static_cast<float>( getUInt(65535) ) / 65535.0f );
    }
    
    //  float limit
    float getFloat( float limit ){
        return getFloat() * limit;
    }

private:
    RandomAlgorithm algorithm_;

};


} // namespace t3

#endif // TRI_RANDOM_NUMBER_GENERATOR_HPP_INCLUDED
