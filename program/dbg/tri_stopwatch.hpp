#ifndef TRI_STOPWATCH_HPP_INCLUDED
#define TRI_STOPWATCH_HPP_INCLUDED

#include <sys/time.h>

namespace t3 {
inline namespace dbg {
    


inline double getSystemTime(){
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return ((double)(tv.tv_sec) + (double)(tv.tv_usec) * 0.001 * 0.001);
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

    double interval() const {
        return end_time_ - last_start_time_;
    }
private:
    double start_time_;
    double last_start_time_;
    double end_time_;
};


}   //  inline namespace dbg
}   //  namespace t3


#endif // TRI_STOPWATCH_HPP_INCLUDED