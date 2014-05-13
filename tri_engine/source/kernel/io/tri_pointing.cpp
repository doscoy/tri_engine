
#include "tri_pointing.hpp"


namespace t3 {
inline namespace kernel {

Pointing::Pointing()
    : hold_(false)
    , trigger_(false)
    , release_(false)
    , repeat_(false)
    , double_click_(false)
    , position_()
    , moving_(0, 0)
    , double_click_timer_(0.0f)
    , double_click_release_count_(0)
    , repeat_interval_(0.1f)
    , pressed_time_(0.0f)
{
    clearPositionList();
}



Pointing::~Pointing()
{

}

void Pointing::updatePointing(
    const PointingData& data,
    tick_t delta_time
){
    bool hit = data.hit_;

    //  入力状態設定
    trigger_ = hit & (hit ^ hold_);
    release_ = hold_ & (hit ^ hold_);
    hold_ = hit;
    
    updateRepeat(delta_time);
    
    //  座標設定
    for (int pos_idx = MAX_POSITION_SIZE-1; pos_idx > 0; --pos_idx) {
        
        position_[pos_idx] = position_[pos_idx-1];
        
    }
    position_[0].x_ = data.x_;
    position_[0].y_ = data.y_;

    //  移動量設定
    moving_ = position_[0] - position_[1];
    
    
    //  ダブルクリック判定
    double_click_ = false;
    if (double_click_timer_ > 0) {
        double_click_timer_ -= delta_time;
        if (release_) {
            double_click_release_count_ += 1;
            if (double_click_release_count_ == 2) {
                double_click_ = true;
                double_click_timer_ = 0.0f;
            }
        }
    }
    else {
        if (trigger_) {
            double_click_timer_ = 0.3f;
            double_click_release_count_ = 0;
        }
    }
    
}


void Pointing::clearPositionList() {
    for (int pos_idx = 0; pos_idx < MAX_POSITION_SIZE; ++pos_idx) {
        position_[pos_idx].x_ = 0;
        position_[pos_idx].y_ = 0;
    }
}


void Pointing::updateRepeat(tick_t delta_time) {
    repeat_ = trigger_;
    if (hold_) {
        pressed_time_ += delta_time;
        if (pressed_time_ > repeat_interval_) {
            pressed_time_ = 0;
            repeat_ = true;
        }
    }
    else {
        pressed_time_ = 0;
    }
}


}   // namespace platform
}   // namespace t3


