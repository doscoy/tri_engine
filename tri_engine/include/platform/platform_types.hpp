#ifndef PLATFORM_TYPES_HPP_INCLUDED
#define PLATFORM_TYPES_HPP_INCLUDED


#include <cstdint>

namespace t3 {
inline namespace platform {

//  プラットフォームから取得するパッドデータ
struct GamePadData {
    
    GamePadData()
        : button_data_(0)
        , stick1x_(0)
        , stick1y_(0)
        , stick2x_(0)
        , stick2y_(0)
        , trigger_l_(0)
        , trigger_r_(0)
    {
    }
    
    
    uint32_t getButtonData() const {
        return button_data_;
    }
    
    uint32_t button_data_;
    float stick1x_;
    float stick1y_;
    float stick2x_;
    float stick2y_;
    float trigger_l_;
    float trigger_r_;
    
    void clearData() {
        button_data_ = 0;
        stick1x_ = 0;
        stick1y_ = 0;
        stick2x_ = 0;
        stick2y_ = 0;
        trigger_l_ = 0;
        trigger_r_ = 0;
    }
    
};


//  プラットフォームから取得するポインティングデータ
// マウス、タッチパネル等
struct PointingData {

    PointingData()
        : x_(0.0f)
        , y_(0.0f)
        , hit_(false)
    {
    }
    
    float x_;
    float y_;
    bool hit_;
    
    void clearData() {
        x_ = 0;
        y_ = 0;
        hit_ = false;
    }
    
};


struct AccelerometerData {
    AccelerometerData()
        : x_(0)
        , y_(0)
        , z_(0)
    {
    }


    float x_;
    float y_;
    float z_;
};


}   // namespace platform
}   // namespace t3

#endif // PLATFORM_TYPES_HPP_INCLUDED
