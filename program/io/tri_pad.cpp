
#include "tri_pad.hpp"


namespace t3{


Pad::Pad()
    : last_frame_data_(0)
    , trigger_(0)
    , release_(0)
    , repeat_(0)
    , repeat_time_(0.5f)
{

}

Pad::~Pad()
{

}

void Pad::updatePad( const u_int current_frame_data )
{
        
    trigger_ = current_frame_data & ( current_frame_data ^ last_frame_data_);
    release_ = last_frame_data_ & ( current_frame_data ^ last_frame_data_);
    
    last_frame_data_ = current_frame_data;
}
    
}   // namespace t3


