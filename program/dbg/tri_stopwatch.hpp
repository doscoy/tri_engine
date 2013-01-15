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
//        gettimeofday( &time_start_, nullptr );
        start_time_ = getSystemTime();
    }

    void end(){
//        gettimeofday( &time_end_, nullptr );
        end_time_ = getSystemTime();
    }

    double interval() const {
//        double startTime = time_start_.tv_sec + time_start_.tv_usec * 1e-6;
//        double endTime = time_end_.tv_sec + time_end_.tv_usec * 1e-6;
//        return endTime - startTime;
        return end_time_ - start_time_;
    }
private:    
//    timeval time_start_;
//    timeval time_end_;
    double start_time_;
    double end_time_;
};


}   //  inline namespace dbg
}   //  namespace t3


#endif // TRI_STOPWATCH_HPP_INCLUDED