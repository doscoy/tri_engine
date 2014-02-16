#ifndef PLATFORM_TYPES_HPP_INCLUDED
#define PLATFORM_TYPES_HPP_INCLUDED


#include <cstdint>

namespace t3 {
namespace platform {

//  プラットフォームから取得するパッドデータ
struct GamePadData {
    
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
};


//  プラットフォームから取得するポインティングデータ
// マウス、タッチパネル等
struct PointingData {
    float x_;
    float y_;
    bool hit_;
};


}   // namespace platform
}   // namespace t3

#endif // PLATFORM_TYPES_HPP_INCLUDED
