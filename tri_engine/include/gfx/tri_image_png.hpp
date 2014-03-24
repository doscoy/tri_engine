
#ifndef TRI_PNG_HPP_INCLUDED
#define TRI_PNG_HPP_INCLUDED

#include "../base/tri_types.hpp"
#include <string>

namespace t3 {
    
struct PngImage {
    
    explicit PngImage(std::string path);
    ~PngImage();
    uint32_t width_;
    uint32_t height_;
    uint8_t* data_;
    int bit_depth_;
    int color_type_;
    int interlace_type_;
    int size_;
};


}   // namespace t3

#endif // TRI_PNG_HPP_INCLUDED
