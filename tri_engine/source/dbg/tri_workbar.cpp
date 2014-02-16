#include "tri_workbar.hpp"
#include "tri_assert.hpp"
#include "tri_print.hpp"
#include "tri_draw_primitive.hpp"
#include "util/tri_util.hpp"
#include <algorithm>

namespace  {
constexpr int KEEP_TIME = 45;
constexpr int RETURN_LIMIT_TIME = 140;

}   // unname namespace

namespace t3 {
inline namespace dbg {

Workbar::Workbar()
    : bar_params_()
    , bar_colors_{{
        Color::orange(),
        Color::lime(),
        Color::aqua(),
        Color::green(),
        Color::orange()}}
    , limit_param_(util::frameSec<60>())
    , limit_width_pixel_(100)
    , keep_frame_(0)
    , limit_bar_pos_x_(0)
    , thickness_(2)
    , position_()
{
    std::fill( bar_params_.begin(), bar_params_.end(), 0 );
}


Workbar::~Workbar()
{
    
}

void Workbar::setColor(
    int index,
    const Color& color
){
    T3_ASSERT( MAX_WORKBAR_ITEM > index );
    bar_colors_[index] = color;
}

void Workbar::setParam(
    int index,
    float param
){
    T3_ASSERT( MAX_WORKBAR_ITEM > index );
    bar_params_[index] = param;
}



void Workbar::draw()
{
    float start_x = position_.x_;
    float y = position_.y_;
    
    for ( int idx = 0; idx < MAX_WORKBAR_ITEM; ++idx ){
        double param = bar_params_[idx];
        double pixel_width = ( param / limit_param_ ) * limit_width_pixel_;
        if ( pixel_width < 1){
            continue;
        }
        drawRectangle( Vec2( start_x, y ), Vec2( pixel_width, thickness_ ), bar_colors_[idx] );
        start_x += pixel_width;
    }
    
    //  上限バーの更新
    if ( start_x > limit_bar_pos_x_ ){
        //  最大値が更新された
        limit_bar_pos_x_ = start_x;
        keep_frame_ = 0;
    }
    
    if ( keep_frame_ < KEEP_TIME ){
        //  しばらく上限をキープ
        keep_frame_ += 1;
    }
    else if ( keep_frame_ < RETURN_LIMIT_TIME ){
        // ちょっとずつ戻ってくる
        limit_bar_pos_x_ -= 1;
        keep_frame_ += 1;
    }
    else {
        limit_bar_pos_x_ = 0;
    }
    
    //  上限バー描画
    drawRectangle( Vec2( limit_bar_pos_x_, y-1 ), Vec2( 1, thickness_+2 ), Color::lime() );
    
}





}   // inline namespace dbg
}   // namespace t3