//  メルセンヌ・ツイスタ

#ifndef TRI_RANDOM_MT_HPP_INCLUDED
#define TRI_RANDOM_MT_HPP_INCLUDED

#include "base/tri_std.hpp"


namespace t3 {

class RandomMT {

public:
	explicit RandomMT( const uint32_t seed );
	
	~RandomMT();
	
public:
	uint32_t getUInt();
	
private:
	void nextState();


private:
	enum {
		MAX_WORK = 624,
	};
	uint32_t state_[MAX_WORK];
	int left_;
	uint32_t* next_;

};

} // namespace t3


#endif // TRI_RANDOM_MT_HPP_INCLUDED
