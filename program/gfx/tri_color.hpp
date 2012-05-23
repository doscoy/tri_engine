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
    color_t() = default;
    color_t( const color_t& ) = default;
    
    color_t(
        u_char color_r,
        u_char color_g,
        u_char color_b,
        u_char color_a = 255
    )   : r( color_r )
        , g( color_g )
        , b( color_b )
        , a( color_a )
    {
    }




    u_char r;
    u_char g;
    u_char b;
    u_char a;
};


const color_t COLOR_BLACK(      0x00, 0x00, 0x00 );
const color_t COLOR_DARKGRAY(   0xA9, 0xA9, 0xA9 );
const color_t COLOR_GRAY(       0x80, 0x80, 0x80 );
const color_t COLOR_LIGHTGRAY(  0xD3, 0xD3, 0xD3 );
const color_t COLOR_WHITE(      0xFF, 0xFF, 0xFF );

const color_t COLOR_RED(        0xFF, 0x00, 0x00 );
const color_t COLOR_LIME(       0x00, 0xFF, 0x00 );
const color_t COLOR_BLUE(       0x00, 0x00, 0xFF );
const color_t COLOR_MAGENTA(    0xFF, 0x00, 0xFF );
const color_t COLOR_ORANGE(     0xFF, 0xA5, 0x00 );
const color_t COLOR_GREEN(      0x00, 0x80, 0x00 );
const color_t COLOR_AQUA(       0x00, 0xFF, 0xFF );
const color_t COLOR_VIOLET(     0xEE, 0x82, 0xEE );
const color_t COLOR_YELLOW(     0xFF, 0xFF, 0x00 );



}   // namespace t3


#endif // TRI_COLOR_HPP_INCLUDED