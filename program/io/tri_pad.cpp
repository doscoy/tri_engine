
#include "tri_pad.hpp"


namespace t3{


Pad::Pad()
    : last_frame_data_(0)
    , trigger_(0)
    , release_(0)
    , repeat_(0)
    , repeat_start_time_(0.35f)
    , repeat_interval_(0.125f)
    , pressed_time_(0.0)
{

}

Pad::~Pad()
{

}

void Pad::updatePad( const u_int current_frame_data, tick_t tick )
{
        
    trigger_ = current_frame_data & ( current_frame_data ^ last_frame_data_);
    release_ = last_frame_data_ & ( current_frame_data ^ last_frame_data_);
    
    last_frame_data_ = current_frame_data;
    
    updateRepeat(tick);
}


void Pad::updateRepeat( tick_t tick )
{
    
    if ( last_frame_data_ > 0 ){
        //  何か一つでもボタンが押され続けている時間を計測
        pressed_time_ += tick;
    }
    else{
        //  何も押されてないフレーム
        pressed_time_ = 0;
    }
    
    
    
    //  リピート判定タイミングになったらリピートデータに反映
    if ( pressed_time_ > repeat_start_time_ + repeat_interval_ ){
        pressed_time_ = repeat_start_time_;
        repeat_ = last_frame_data_;
    }
    else {
        //  リピート判定はトリガーも含む
        repeat_ = trigger_;
    }
    
}



}   // namespace t3


