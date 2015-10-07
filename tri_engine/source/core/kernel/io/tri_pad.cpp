////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/kernel/io/tri_pad.hpp"


TRI_CORE_NS_BEGIN



Pad::Pad()
    : last_frame_data_(0)
    , trigger_(0)
    , release_(0)
    , repeat_(0)
    , repeat_start_time_(0.35f)
    , repeat_interval_(0.125f)
    , pressed_time_(0.0)
    , left_stick_()
    , right_stick_()
    , l_trigger_(0.0f)
    , r_trigger_(0.0f)
{
}

Pad::~Pad() {

}

void Pad::updatePad(const cross::GamePadData& paddata, DeltaTime delta_time) {
    uint32_t current_frame_data = paddata.buttonData();
    trigger_ = current_frame_data & (current_frame_data ^ last_frame_data_);
    release_ = last_frame_data_ & (current_frame_data ^ last_frame_data_);
    
    last_frame_data_ = current_frame_data;
    
    updateRepeat(delta_time);
    
    
    //  スティックデータ更新
    left_stick_.x_ = paddata.stick1x_;
    left_stick_.y_ = paddata.stick1y_;
    right_stick_.x_ = paddata.stick2x_;
    right_stick_.y_ = paddata.stick2y_;

    l_trigger_ = paddata.trigger_l_;
    r_trigger_ = paddata.trigger_r_;

}


void Pad::updateRepeat(DeltaTime delta_time) {
    
    if (last_frame_data_ > 0) {
        //  何か一つでもボタンが押され続けている時間を計測
        pressed_time_ += delta_time;
    }
    else {
        //  何も押されてないフレーム
        pressed_time_ = 0;
    }
    
    
    
    //  リピート判定タイミングになったらリピートデータに反映
    if (pressed_time_ > repeat_start_time_ + repeat_interval_) {
        pressed_time_ = repeat_start_time_;
        repeat_ = last_frame_data_;
    }
    else {
        //  リピート判定はトリガーも含む
        repeat_ = trigger_;
    }
    
}



TRI_CORE_NS_END

