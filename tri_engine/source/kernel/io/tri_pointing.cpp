
#include "tri_pointing.hpp"
#include "base/tri_director.hpp"

namespace t3 {
inline namespace kernel {

Pointing::Pointing()
    : hold_(false)
    , trigger_(false)
    , release_(false)
    , repeat_(false)
    , moved_(false)
    , double_click_(false)
    , position_()
    , moving_(0, 0)
    , double_click_timer_(0.0f)
    , double_click_release_count_(0)
    , repeat_interval_(0.1f)
    , pressed_time_(0.0f)
    , pointing_count_(0)
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


    pointing_count_ = data.getPointingCount();

    //  入力状態設定
    trigger_ = hit & (hit ^ hold_);
    release_ = hold_ & (hit ^ hold_);
    hold_ = hit;
    
    updateRepeat(delta_time);
    
    //  座標系補正
    //  仮想スクリーン座標に変換
    const Vec2& revise = t3::Director::instance().screenRevise();
    float new_point_x = data.x_ * revise.x_;
    float new_point_y = data.y_ * revise.y_;
    
    
    //  座標設定
    for (int pos_idx = MAX_POSITION_SIZE-1; pos_idx > 0; --pos_idx) {
        
        position_[pos_idx] = position_[pos_idx-1];
        
    }
    position_[0].x_ = new_point_x;
    position_[0].y_ = new_point_y;

    //  移動量設定
    moving_ = position_[0] - position_[1];
    
    //  移動判定設定
    if (isZeroFloat(moving_.x_) && isZeroFloat(moving_.y_)) {
        moved_ = false;
    }
    else {
        moved_ = true;
    }
    
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


