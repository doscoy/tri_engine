#ifndef TRI_COLOR_HPP_INCLUDED
#define TRI_COLOR_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"


namespace t3 {

///
/// RGBA�J���[�^
typedef uint32_t rgba32_t;

///
/// �F
class Color {

public:
    ///
    /// �R���X�g���N�^
    Color()
        : Color(255, 255, 255, 255)
    {}
    
    ///
    /// �f�X�g���N�^
    ~Color() = default;

    ///
    /// �R���X�g���N�^
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
    ///
    /// ����F����
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
    ///
    /// rgba32bit�Ƃ��Ď擾
    rgba32_t rgba32() const {
        return (red_ << 24 | green_ << 16 | blue_ << 8 | alpha_);
    }
    
    ///
    /// �Ԏ擾.
    float redFloat() const {
        return static_cast<float>(red_) / 255.0f;
    }

    ///
    /// �Ύ擾.
    float greenFloat() const {
        return static_cast<float>(green_) / 255.0f;
    }

    ///
    /// �擾.
    float blueFloat() const {
        return static_cast<float>(blue_) / 255.0f;
    }

    ///
    /// �A���t�@�擾.
    float alphaFloat() const {
        return static_cast<float>(alpha_) / 255.0f;
    }
    
    ///
    /// �A���t�@�ݒ�.
    void alphaFloat(const float a) {
        alpha_ = static_cast<std::uint8_t>(255.0f * a);
        if (alpha_ > 255) {
            alpha_ = 255;
        }
        else if (alpha_ < 0) {
            alpha_ = 0;
        }
    }
    
    ///
    /// �Ԑݒ�.
    void redFloat(const float r) {
        red(static_cast<uint_fast8_t>(255.0f * r));
    }
    
    ///
    /// �ΐݒ�.
    void greenFloat(const float g) {
        green(static_cast<uint_fast8_t>(255.0f * g));
    }
    
    ///
    /// �ݒ�.
    void blueFloat(const float b) {
        blue(static_cast<uint_fast8_t>(255.0f * b));
    }
    

    ///
    /// �Ԑݒ�.
    void red(uint_fast8_t r) {
        if (r > 255) {
            r = 255;
        } else if (r < 0) {
            r = 0;
        }
        red_ = r;
    }
    
    ///
    /// �ΐݒ�.
    void green(uint_fast8_t g) {
        if (g > 255) {
            g = 255;
        } else if (g < 0) {
            g = 0;
        }
        green_ = g;
    }
    
    ///
    /// �ݒ�.
    void blue(uint_fast8_t b) {
        if (b > 255) {
            b = 255;
        } else if (b < 0) {
            b = 0;
        }
        blue_ = b;
    }
    
    ///
    /// �A���t�@�ݒ�.
    void alpha(uint_fast8_t a) {
        if (a > 255) {
            a = 255;
        } else if (a < 0) {
            a = 0;
        }
        alpha_ = a;
    }

    ///
    /// �Ԏ擾.
    uint_fast8_t red() const {
        return red_;
    }

    ///
    /// �Ύ擾.
    uint_fast8_t green() const {
        return green_;
    }
    
    ///
    /// �擾.
    uint_fast8_t blue() const {
        return blue_;
    }
    
    ///
    /// �A���t�@�擾.
    uint_fast8_t alpha() const {
        return alpha_;
    }
    
private:
    uint8_t red_;   ///< ��
    uint8_t blue_;  ///< ��
    uint8_t green_; ///< ��
    uint8_t alpha_; ///< �A���t�@

};



namespace color_sample {

    inline Color red() {

        return Color(0xff, 0x00, 0x00);
    }

    inline Color green() {

        return Color(0x00, 0xff, 0x00);
    }

    inline Color blue() {

        return Color(0x00, 0x00, 0xff);
    }

    inline Color black() {

        return Color(0x00, 0x00, 0x00);
    }


    inline Color blueivy() {
        return Color(0x30, 0x90, 0xc7);
    }

    inline Color oceanblue() {
        return Color(0x2b, 0x65, 0xec);
    }

    inline Color skyblue() {
        return Color(0x66, 0x98, 0xff);
    }

    inline Color azure() {
        return Color(0xf0, 0xff, 0xff);
    }

    inline Color darkgray() {
        return Color(0xA9, 0xA9, 0xA9);
    }

    inline Color gray() {
        return Color(0x80, 0x80, 0x80);
    }

    inline Color lightgray() {
        return Color(0xD3, 0xD3, 0xD3);
    }

    inline Color white() {
        return Color(0xFF, 0xFF, 0xFF);
    }


    inline Color lime() {
        return Color(0x00, 0xFF, 0x00);
    }

    inline Color magenta() {
        return Color(0xFF, 0x00, 0xFF);
    }

    inline Color orange() {
        return Color(0xFF, 0xA5, 0x00);
    }


    inline Color cyan() {
        return Color(0x00, 0xFF, 0xFF);
    }

    inline Color violet() {
        return Color(0xEE, 0x82, 0xEE);
    }

    inline Color yellow() {
        return Color(0xFF, 0xFF, 0x00);
    }

    inline Color pinc() {
        return Color(0xFA, 0xAF, 0xBE);
    }

    inline Color lightpink() {
        return Color(0xFA, 0xAF, 0xBA);
    }

    inline Color olive() {
        return Color(0x80, 0x80, 0x00);
    }

    inline Color brown() {
        return Color(0xa5, 0x2a, 0x2a);
    }

    inline Color silver() {
        return Color(0xc0, 0xc0, 0xc0);
    }

    inline Color yellowgreen() {
        return Color(0x52, 0xd0, 0x17);
    }

    inline Color forestgreen() {
        return Color(0x22, 0x8b, 0x22);
    }

    inline Color purple() {
        return Color(0x80, 0x00, 0x80);
    }

    inline Color khaki() {
        return Color(0xf0, 0xe6, 0x8c);
    }

}   // namespace color_sample



}   // namespace t3





#endif // TRI_COLOR_HPP_INCLUDED