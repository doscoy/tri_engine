#include "dbg/tri_debug_log_layer.hpp"
#include "gfx/tri_color.hpp"

#include "dbg/tri_print.hpp"
#include "base/tri_director.hpp"
#include "dbg/tri_draw_primitive.hpp"



namespace t3 {

constexpr int DEBUG_LOG_LINE = 43;

DebugLogLayer::DebugLogLayer(const char* const name)
    : DebugStringLayer(name)
    , debug_log_buffer_()
    , log_show_offset_(0)
{
    hideLayer();
}


DebugLogLayer::~DebugLogLayer()
{
}

void DebugLogLayer::writeString(
    const char* const str
) {
    //  ログバッファに文字列を登録
    debug_log_buffer_.addString(str);
}


void DebugLogLayer::updateLayer(tick_t delta_time)
{
    //  表示予定が無ければ処理しない
    if (!isVisibleLayer()) {
        return;
    }

    if (debug_log_buffer_.getStringCount() == 0) {
        //  一つも登録されてないので即抜け
        return;
    }


    DebugStringLayer::updateLayer(delta_time);
    

    int str_idx = getLogShowLineIndex();
    
    int line = str_idx;
    if (line > DEBUG_LOG_LINE) {
        line = DEBUG_LOG_LINE;
    }

    //  下から順番にログを書く
    for (; line >= 0; --line) {
        DebugStringLayer::writeString(
            30.0f,
            static_cast<float>(line * DEBUG_FONT_POINT),
            color_sample::white().rgba32(),
            DEBUG_FONT_POINT,
            debug_log_buffer_.getString(str_idx)
        );
        --str_idx;
    }
    
    auto& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();

    if (pad.isPress(t3::Pad::BUTTON_DOWN)) {
        slideDown();
    }
    if (pad.isPress(t3::Pad::BUTTON_UP)) {
        slideUp();
    }

}

void DebugLogLayer::drawLayer()
{
    auto& gs = t3::Director::instance();
    
    //  文字列が見やすいように背景に半透明の板を描画
    cross::RenderSystem::setDepthTestMode(cross::RenderSystem::DepthTestMode::MODE_ALWAYS);
    cross::RenderSystem::setBlend(true);

    Color bg_color = Color(0, 0, 0, 80);
    drawRectangleMinSize(
        Vec2(0, 0),
        Vec2(gs.virtualScreenSize().x_, gs.virtualScreenSize().y_),
        bg_color
    );
    

    //  文字列の描画はDebugStringLayerに任せる
    DebugStringLayer::drawLayer();
}



int DebugLogLayer::getLogShowLineIndex() const {

    int index = static_cast<int>(debug_log_buffer_.getStringCount() -1 - log_show_offset_);
    
    return index;
}

void DebugLogLayer::slideUp()
{
    if (getLogShowLineIndex() > DEBUG_LOG_LINE) {
        log_show_offset_ += 1;
    }
}


void DebugLogLayer::slideDown()
{
    if (log_show_offset_ > 0) {
        log_show_offset_ -= 1;
    }
}


}   // namespace t3
