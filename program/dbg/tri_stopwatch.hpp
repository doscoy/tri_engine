#ifndef TRI_STOPWATCH_HPP_INCLUDED
#define TRI_STOPWATCH_HPP_INCLUDED

#include <sys/time.h>

namespace t3 {

class Stopwatch
{
public:
    void start(){
        gettimeofday( &ts_, nullptr );
    }

    void end(){
        gettimeofday( &te_, nullptr );        
    }

    double interval() const {
        double startTime = ts_.tv_sec + ts_.tv_usec * 1e-6;
        double endTime = te_.tv_sec + te_.tv_usec * 1e-6;
        return endTime - startTime;
    }
private:    
    timeval ts_;
    timeval te_;
};

}   // namespace t3


#endif // TRI_STOPWATCH_HPP_INCLUDED