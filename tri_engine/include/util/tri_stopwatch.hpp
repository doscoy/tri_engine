#ifndef TRI_STOPWATCH_HPP_INCLUDED
#define TRI_STOPWATCH_HPP_INCLUDED


#include <chrono>

namespace t3 {

    
//using Time = std::chrono::system_clock::time_point;

	typedef std::chrono::time_point<std::chrono::steady_clock> Time;
inline Time getSystemTime(){
    return std::chrono::high_resolution_clock::now();
}


class Stopwatch
{
public:
    void start(){
        start_time_ = getSystemTime();
    }

    void end(){
        end_time_ = getSystemTime();
        last_start_time_ = start_time_;
    }

//    std::chrono::microseconds interval() const {
//        return std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - last_start_time_);
//    }

	float interval() const {

		return 0.1f;
	}
private:
    Time start_time_;
    Time last_start_time_;
    Time end_time_;
};


}   //  namespace t3


#endif // TRI_STOPWATCH_HPP_INCLUDED