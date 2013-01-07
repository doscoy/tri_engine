#ifndef TRI_COLOR_HPP_INCLUDED
#define TRI_COLOR_HPP_INCLUDED

#include "tri_basetypes.hpp"
#include "../platform/platform_sdk.hpp"

namespace t3 {

enum ColorFormat
{
    RGBA = GL_RGBA,
    RGB  = GL_RGB,
};

struct color_t
{
    u_char r;
    u_char g;
    u_char b;
    u_char a;
};


class Color : public color_t
{
public:
    Color() = default;
    ~Color() = default;
    Color(
        const u_char red,
        const u_char green,
        const u_char blue,
        const u_char alpha = 255
    ){
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
    
public:
    u_char red() const {
        return r;
    }
    u_char green() const {
        return g;
    }
    u_char blue() const {
        return b;
    }
    u_char alpha() const {
        return a;
    }
    
    float redf() const {
        return static_cast<float>(r) / 255.0f;
    }
    float greenf() const {
        return static_cast<float>(g) / 255.0f;
    }
    float bluef() const {
        return static_cast<float>(b) / 255.0f;
    }
    float alphaf() const {
        return static_cast<float>(a) / 255.0f;
    }
};

inline Color& toColorClass( color_t& color )
{
    return static_cast<Color&>(color);
}



const Color COLOR_BLACK(      0x00, 0x00, 0x00 );
const Color COLOR_DARKGRAY(   0xA9, 0xA9, 0xA9 );
const Color COLOR_GRAY(       0x80, 0x80, 0x80 );
const Color COLOR_LIGHTGRAY(  0xD3, 0xD3, 0xD3 );
const Color COLOR_WHITE(      0xFF, 0xFF, 0xFF );

const Color COLOR_RED(        0xFF, 0x00, 0x00 );
const Color COLOR_LIME(       0x00, 0xFF, 0x00 );
const Color COLOR_BLUE(       0x00, 0x00, 0xFF );
const Color COLOR_MAGENTA(    0xFF, 0x00, 0xFF );
const Color COLOR_ORANGE(     0xFF, 0xA5, 0x00 );
const Color COLOR_GREEN(      0x00, 0x80, 0x00 );
const Color COLOR_AQUA(       0x00, 0xFF, 0xFF );
const Color COLOR_VIOLET(     0xEE, 0x82, 0xEE );
const Color COLOR_YELLOW(     0xFF, 0xFF, 0x00 );



}   // namespace t3


#endif // TRI_COLOR_HPP_INCLUDED