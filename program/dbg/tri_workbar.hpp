#ifndef TRI_WORKBAR_HPP_INCLUDED
#define TRI_WORKBAR_HPP_INCLUDED

#include "../util/tri_uncopyable.hpp"
#include "../math/tri_vec2.hpp"
#include "../gfx/tri_color.hpp"
#include <array>

namespace t3 {
inline namespace dbg {
constexpr int MAX_WORKBAR_ITEM = 15;

class Workbar
    : Uncopyable
{
public:
    Workbar(
        float limit_param,
        int limit_width_pixel
    );
    ~Workbar();


public:
    void setColor( int index, const color_t& color );
    void setParam( int index, float param );
    void setPosition( const vec2_t& pos ){
        position_ = pos;
    }
    
    void setLimitParam( float limit ){
        limit_param_ = limit;
    }
    
    void setLimitWidthPixel( int width ){
        limit_width_pixel_ = width;
    }
    
    void setTickness( int thickness ){
        thickness_ = thickness;
    }
    
    void draw();
    
    
private:
    std::array<float, MAX_WORKBAR_ITEM> bar_params_;
    std::array<color_t, MAX_WORKBAR_ITEM> bar_colors_;
    float limit_param_;
    int limit_width_pixel_;
    int keep_frame_;
    int limit_bar_pos_x_;
    int thickness_;
    vec2_t position_;
};


}   // inline namespace dbg
}   // namespace t3





#endif // TRI_WORKBAR_HPP_INCLUDED