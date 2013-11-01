#ifndef TRI_COLOR_HPP_INCLUDED
#define TRI_COLOR_HPP_INCLUDED

#include "../platform/platform_sdk.hpp"

namespace t3 {

typedef uint32_t rgba32_t;

enum ColorFormat
{
    RGBA = GL_RGBA,
    RGB  = GL_RGB,
};


class Color
{
public:
    uint8_t red_;
    uint8_t blue_;
    uint8_t green_;
    uint8_t alpha_;

public:
    Color() = default;
    ~Color() = default;
    Color(
        const uint8_t red,
        const uint8_t green,
        const uint8_t blue,
        const uint8_t alpha = 255
    ){
        red_ = red;
        green_ = green;
        blue_ = blue;
        alpha_ = alpha;
    }
    
public:
    
    rgba32_t getRGBA() const {
        return (red_ << 24 | green_ << 16 | blue_ << 8 | alpha_);
    }
    
    float redf() const {
        return static_cast<float>(red_) / 255.0f;
    }
    float greenf() const {
        return static_cast<float>(green_) / 255.0f;
    }
    float bluef() const {
        return static_cast<float>(blue_) / 255.0f;
    }
    float alphaf() const {
        return static_cast<float>(alpha_) / 255.0f;
    }
    
    
    static Color black() {
        return Color(0x00, 0x00, 0x00);
    }
    
    static Color blue() {
        return Color(0x00, 0x00, 0xFF);
    }
    
    static Color darkgray() {
        return Color( 0xA9, 0xA9, 0xA9 );
    }
    
    static Color gray() {
        return Color( 0x80, 0x80, 0x80 );
    }

    static Color lightgray() {
        return Color( 0xD3, 0xD3, 0xD3 );
    }
    
    static Color white() {
        return Color( 0xFF, 0xFF, 0xFF );
    }
    
    static Color red() {
        return Color( 0xFF, 0x00, 0x00 );
    }
    
    static Color lime() {
        return Color( 0x00, 0xFF, 0x00 );
    }

    static Color magenta() {
        return Color( 0xFF, 0x00, 0xFF );
    }
    
    static Color orange() {
        return Color(     0xFF, 0xA5, 0x00 );
    }
    
    static Color green() {
        return Color( 0x00, 0x80, 0x00 );
    }


    static Color aqua() {
        return Color( 0x00, 0xFF, 0xFF );
    }

    static Color violet() {
        return Color( 0xEE, 0x82, 0xEE );
    }
    
    static Color yellow() {
        return Color( 0xFF, 0xFF, 0x00 );
    }
    
    
    
};

inline Color& toColorClass( Color& color )
{
    return static_cast<Color&>(color);
}






}   // namespace t3


#endif // TRI_COLOR_HPP_INCLUDED