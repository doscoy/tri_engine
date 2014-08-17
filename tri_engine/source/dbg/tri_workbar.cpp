#include "dbg/tri_workbar.hpp"
#include "dbg/tri_assert.hpp"
#include "dbg/tri_print.hpp"
#include "dbg/tri_draw_primitive.hpp"
#include "util/tri_util.hpp"
#include <algorithm>
#include <limits>

namespace  {
constexpr int KEEP_TIME = 45;
constexpr int RETURN_LIMIT_TIME = 140;

}   // unname namespace

namespace t3 {
inline namespace dbg {

Workbar::Workbar()
    : bar_params_()
    , limit_param_(util::frameSec<60>())
    , limit_width_pixel_(200)
    , keep_frame_(0)
    , limit_bar_pos_x_(std::numeric_limits<int>::min())
    , thickness_(2)
    , position_()
{
    bar_params_[0] = {0, Color::magenta()};
    bar_params_[1] = {0, Color::yellow()};
    bar_params_[2] = {0, Color::green()};
    bar_params_[3] = {0, Color::cyan()};
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


#ifdef NDEBUG
    return;
#endif  // NDEBUG

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
        drawRectangle(
            Vec2(start_x, y),
            Vec2(pixel_width, thickness_),
            param.color_
        );
        start_x += pixel_width;
        total_param += param.value_;
    }
    
    
    //  目安の縦棒を描画
    //  0%
    drawRectangle(
        Vec2(position_.x_, y-5),
        Vec2(1, 10),
        Color::silver()
    );
    
    //  100%
    drawRectangle(
        Vec2(position_.x_ + limit_width_pixel_, y-5),
        Vec2(1, 10),
        Color::silver()
    );
    
    //  25%区切り
    int per25pixel = limit_width_pixel_ / 4;
    
    //  50%
    drawRectangle(
        Vec2(0, y-3),
        Vec2(1, 6),
        Color::silver()
    );
    
    //  25%
    drawRectangle(
        Vec2(-per25pixel, y-3),
        Vec2(1, 6),
        Color::silver()
    );
    
    //  75%
    drawRectangle(
        Vec2(per25pixel, y-3),
        Vec2(1, 6),
        Color::silver()
    );
    
    //  上限バーの更新
    if (start_x > limit_bar_pos_x_) {
        //  最大値が更新された
        limit_bar_pos_x_ = start_x;
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
    Color limit_bar_color = Color::lime();
    if (limit_bar_pos_x_ > 0) {
        limit_bar_color = Color::red();
    }
    drawRectangle(Vec2(limit_bar_pos_x_, y-1), Vec2(3, thickness_+2), limit_bar_color);
    
}





}   // inline namespace dbg
}   // namespace t3