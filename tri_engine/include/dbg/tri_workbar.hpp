#ifndef TRI_WORKBAR_HPP_INCLUDED
#define TRI_WORKBAR_HPP_INCLUDED

#include "../util/tri_uncopyable.hpp"
#include "../math/tri_vec2.hpp"
#include "../gfx/tri_color.hpp"
#include <array>

namespace t3 {
inline namespace dbg {
constexpr int MAX_WORKBAR_ITEM = 6;

class Workbar
    : private Uncopyable
{
public:
    Workbar();
    ~Workbar();


public:
    void setColor(int index, const Color& color);
    void setParam(int index, float param);
    void position(const Vec2& pos) {
        position_ = pos;
    }
    
    void setLimitParam(float limit) {
        limit_param_ = limit;
    }
    
    void setLimitWidthPixel(int width) {
        limit_width_pixel_ = width;
    }
    
    void setTickness(int thickness) {
        thickness_ = thickness;
    }
    
    void draw();
    
    
private:
    struct Param {
        float value_;
        Color color_;
    };
    Array<Param, MAX_WORKBAR_ITEM> bar_params_;
    float limit_param_;
    int limit_width_pixel_;
    int keep_frame_;
    int limit_bar_pos_x_;
    int thickness_;
    Vec2 position_;
};


}   // inline namespace dbg
}   // namespace t3





#endif // TRI_WORKBAR_HPP_INCLUDED