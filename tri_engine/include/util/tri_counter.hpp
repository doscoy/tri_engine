#ifndef TRI_COUNTER_HPP_INCLUDED
#define TRI_COUNTER_HPP_INCLUDED

namespace t3 {

class Counter
{
public:
    Counter()
        : num_( 0 )
    {}
    
    
    
    int now() const {
        return num_;
    }
    
    void countup() {
        num_ += 1;
    }
    
    void countdown() {
        num_ -= 1;
    }
    
private:
    int num_;
};

extern Counter frame_counter_;

}   // namespace t3



#endif // TRI_COUNTER_HPP_INCLUDED