#ifndef TRI_COLOR_HPP_INCLUDED
#define TRI_COLOR_HPP_INCLUDED

#include "base/tri_std.hpp"


namespace t3 {

typedef uint32_t rgba32_t;

class Color
{
private:
    uint8_t red_;
    uint8_t blue_;
    uint8_t green_;
    uint8_t alpha_;

public:
    Color()
        : Color(255, 255, 255, 255)
    {}
    
    ~Color() = default;
    Color(
        const uint8_t red,
        const uint8_t green,
        const uint8_t blue,
        const uint8_t alpha = 255
    )   : red_(red)
        , green_(green)
        , blue_(blue)
        , alpha_(alpha)
    {
    }
    
public:
    bool operator ==(const Color& rhs) const {
        if (red_ != rhs.red_) {
            return false;
        }
        if (green_ != rhs.green_) {
            return false;
        }
        if (blue_ != rhs.blue_) {
            return false;
        }
        if (alpha_ != rhs.alpha_) {
            return false;
        }
        
        return true;
    }
    
public:
    
    rgba32_t rgba32() const {
        return (red_ << 24 | green_ << 16 | blue_ << 8 | alpha_);
    }
    
    float redFloat() const {
        return static_cast<float>(red_) / 255.0f;
    }
    float greenFloat() const {
        return static_cast<float>(green_) / 255.0f;
    }
    float blueFloat() const {
        return static_cast<float>(blue_) / 255.0f;
    }
    float alphaFloat() const {
        return static_cast<float>(alpha_) / 255.0f;
    }
    
    void alphaFloat(const float a) {
        alpha_ = 255.0f * a;
        if (alpha_ > 255) {
            alpha_ = 255;
        }
        else if (alpha_ < 0) {
            alpha_ = 0;
        }
    }
    
    void redFloat(const float r) {
        red(255.0f * r);
    }
    
    void greenFloat(const float g) {
        green(255.0f * g);
    }
    
    void blueFloat(const float b) {
        blue(255.0f * b);
    }
    


    void red(int r) {
        if (r > 255) {
            r = 255;
        } else if (r < 0) {
            r = 0;
        }
        red_ = r;
    }
    
    void green(int g) {
        if (g > 255) {
            g = 255;
        } else if (g < 0) {
            g = 0;
        }
        green_ = g;
    }
    
    void blue(int b) {
        if (b > 255) {
            b = 255;
        } else if (b < 0) {
            b = 0;
        }
        blue_ = b;
    }
    
    void alpha(int a) {
        if (a > 255) {
            a = 255;
        } else if (a < 0) {
            a = 0;
        }
        alpha_ = a;
    }

    int red() const {
        return red_;
    }

    int green() const {
        return green_;
    }
    
    int blue() const {
        return blue_;
    }
    
    int alpha() const {
        return alpha_;
    }
    
public:
    
    
    static Color BLACK;
    static Color BLUE;
    static Color GREEN;
    static Color RED;
    
    
    static Color blueivy() {
        return Color(0x30, 0x90, 0xc7);
    }
    
    static Color oceanblue() {
        return Color(0x2b, 0x65, 0xec);
    }
    
    static Color skyblue() {
        return Color(0x66, 0x98, 0xff);
    }
    
    static Color azure() {
        return Color(0xf0, 0xff, 0xff);
    }
    
    static Color darkgray() {
        return Color(0xA9, 0xA9, 0xA9);
    }
    
    static Color gray() {
        return Color(0x80, 0x80, 0x80);
    }

    static Color lightgray() {
        return Color(0xD3, 0xD3, 0xD3);
    }
    
    static Color white() {
        return Color(0xFF, 0xFF, 0xFF);
    }
    
    
    static Color lime() {
        return Color(0x00, 0xFF, 0x00 );
    }

    static Color magenta() {
        return Color(0xFF, 0x00, 0xFF);
    }
    
    static Color orange() {
        return Color(0xFF, 0xA5, 0x00);
    }
    

    static Color cyan() {
        return Color(0x00, 0xFF, 0xFF);
    }

    static Color violet() {
        return Color(0xEE, 0x82, 0xEE);
    }
    
    static Color yellow() {
        return Color(0xFF, 0xFF, 0x00);
    }
    
    static Color pinc() {
        return Color(0xFA, 0xAF, 0xBE);
    }
    
    static Color lightpink() {
        return Color(0xFA, 0xAF, 0xBA);
    }
    
    static Color olive() {
        return Color(0x80, 0x80, 0x00);
    }
    
    static Color brown() {
        return Color(0xa5, 0x2a, 0x2a);
    }
    
    static Color silver() {
        return Color(0xc0, 0xc0, 0xc0);
    }
    
    static Color yellowgreen() {
        return Color(0x52, 0xd0, 0x17);
    }
    
    static Color forestgreen() {
        return Color(0x22, 0x8b, 0x22);
    }

    static Color purple() {
        return Color(0x80, 0x00, 0x80);
    }
  
    static Color khaki() {
        return Color(0xf0, 0xe6, 0x8c);
    }
    
};


}   // namespace t3


#endif // TRI_COLOR_HPP_INCLUDED