////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
#include "core/debug/tri_workbar.hpp"
#include "core/debug/tri_assert.hpp"
#include "core/debug/tri_print.hpp"
#include "core/debug/tri_draw_primitive.hpp"
#include "core/utility/tri_util.hpp"
#include <algorithm>
#include <limits>


TRI_CORE_NS_BEGIN

namespace  {
constexpr int KEEP_TIME = 45;
constexpr int RETURN_LIMIT_TIME = 140;

}   // unname namespace



Workbar::Workbar()
    : bar_params_()
    , limit_param_(frameSec<60>())
    , limit_width_pixel_(200)
    , keep_frame_(0)
    , limit_bar_pos_x_(std::numeric_limits<int>::min())
    , thickness_(2)
    , position_()
{
    bar_params_[0] = {0, color_sample::magenta()};
    bar_params_[1] = {0, color_sample::yellow()};
    bar_params_[2] = {0, color_sample::green()};
    bar_params_[3] = {0, color_sample::cyan()};
    bar_params_[4] = {0, color_sample::orange()};
    bar_params_[5] = {0, color_sample::white()};
}


Workbar::~Workbar() {
    
}

void Workbar::setColor(
    int index,
    const Color& color
) {
    T3_ASSERT( MAX_WORKBAR_ITEM > index );
    bar_params_[index].color_ = color;
}

void Workbar::setParam(
    int index,
    float param
) {
    T3_ASSERT( MAX_WORKBAR_ITEM > index );
    bar_params_[index].value_ = param;
}



//  描画
void Workbar::draw() {


#ifndef DEBUG
    return;
#endif  // DEBUG

    //
    float start_x = position_.x_;
    float y = position_.y_;
    float total_param = 0;
    
    
    
    //  計測済の項目それぞれを描画
    for (Param param : bar_params_) {

        float pixel_width = (param.value_ / limit_param_) * limit_width_pixel_;
        if (pixel_width < 1.0){
            continue;
        }
        drawRectangleMinSize(
            Vec2(start_x, y),
            Vec2(pixel_width, static_cast<float>(thickness_)),
            param.color_
        );
        start_x += pixel_width;
        total_param += param.value_;
    }
    
    
    //  目安の縦棒を描画
    //  0%
    drawRectangleMinSize(
        Vec2(position_.x_, y-5),
        Vec2(1, 10),
        color_sample::silver()
    );
    
    //  100%
    drawRectangleMinSize(
        Vec2(position_.x_ + limit_width_pixel_, y-5),
        Vec2(1, 10),
        color_sample::silver()
    );
    
    //  25%区切り
    int per25pixel = limit_width_pixel_ / 4;
    
    //  50%
    drawRectangleMinSize(
        Vec2(0.0f, static_cast<float>(y-3)),
        Vec2(1.0f, 6.0f),
        color_sample::silver()
    );
    
    //  25%
    drawRectangleMinSize(
        Vec2(static_cast<float>(-per25pixel), static_cast<float>(y-3)),
        Vec2(1.0f, 6.0f),
        color_sample::silver()
    );
    
    //  75%
    drawRectangleMinSize(
        Vec2(static_cast<float>(per25pixel), static_cast<float>(y-3)),
        Vec2(1.0f, 6.0f),
        color_sample::silver()
    );
    
    //  上限バーの更新
    if (start_x > limit_bar_pos_x_) {
        //  最大値が更新された
        limit_bar_pos_x_ = static_cast<int>(start_x);
        keep_frame_ = 0;
    }
    
    if (keep_frame_ < KEEP_TIME) {
        //  しばらく上限をキープ
        keep_frame_ += 1;
    }
    else if (keep_frame_ < RETURN_LIMIT_TIME) {
        // ちょっとずつ戻ってくる
        limit_bar_pos_x_ -= 1;
        keep_frame_ += 1;
    }
    else {
        limit_bar_pos_x_ = std::numeric_limits<int>::min();
    }
    
    //  上限バー描画
    auto limit_bar_color = color_sample::lime();
    if (limit_bar_pos_x_ > 0) {
        limit_bar_color = color_sample::red();
    }
    drawRectangleMinSize(
        Vec2(static_cast<float>(limit_bar_pos_x_), y - 1.0f), 
        Vec2(3.0f, static_cast<float>(thickness_ + 2)), 
        limit_bar_color
    );
    
}

TRI_CORE_NS_END
