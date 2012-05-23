//  メルセンヌ・ツイスタ

#ifndef TRI_RANDOM_MT_HPP_INCLUDED
#define TRI_RANDOM_MT_HPP_INCLUDED

#include "../../tri_develop_base.hpp"

namespace t3 {

class RandomMT {

public:
	explicit RandomMT( const u_int seed );
	
	~RandomMT();
	
public:
	u_int getUInt();
	
private:
	void nextState();


private:
	enum {
		MAX_WORK = 624,
	};
	u_int state_[MAX_WORK];
	int left_;
	u_int* next_;

};

} // namespace t3


#endif // TRI_RANDOM_MT_HPP_INCLUDED
