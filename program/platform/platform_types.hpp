#ifndef PLATFORM_TYPES_HPP_INCLUDED
#define PLATFORM_TYPES_HPP_INCLUDED


#include <cstdint>

namespace glue {

//  プラットフォームから取得するキーデータ
typedef uint32_t pad_data_t;

//  プラットフォームから取得するポインティングデータ
struct pointing_data_t {
    int x;
    int y;
    bool hit;
};

//  プラットフォームから取得する加速度センサデータ
struct accele_data_t {
    float x;
    float y;
    float z;
};

}   // namespace glue


#endif // PLATFORM_TYPES_HPP_INCLUDED
