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
    
};


}   // namespace platform
}   // namespace t3

#endif // PLATFORM_TYPES_HPP_INCLUDED
