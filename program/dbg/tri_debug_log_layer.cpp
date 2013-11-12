#include "tri_debug_log_layer.hpp"
#include "../gfx/tri_color.hpp"
#include "tri_print.hpp"
#include "../base/tri_game_system.hpp"
#include "tri_draw_primitive.hpp"



namespace t3 {
inline namespace dbg {

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


void DebugLogLayer::updateLayer(tick_t tick)
{
    //  表示予定が無ければ処理しない
    if (!isVisibleLayer()) {
        return;
    }

    if (debug_log_buffer_.getStringCount() == 0) {
        //  一つも登録されてないので即抜け
        return;
    }


    DebugStringLayer::updateLayer(tick);
    

    int str_idx = getLogShowLineIndex();
    
    int line = str_idx;
    if (line > DEBUG_LOG_LINE) {
        line = DEBUG_LOG_LINE;
    }

    //  下から順番にログを書く
    for (; line >= 0; --line) {
        DebugStringLayer::writeString(
            30,
            line * DEBUG_FONT_POINT,
            Color::white().getRGBA(),
            DEBUG_FONT_POINT,
            debug_log_buffer_.getString(str_idx)
        );
        --str_idx;
    }
    
    GameSystem& gs = t3::GameSystem::getInstance();
    const t3::Pad& pad = gs.getPad();

    if (pad.isPress(t3::Pad::BUTTON_DOWN)) {
        slideDown();
    }
    if (pad.isPress(t3::Pad::BUTTON_UP)) {
        slideUp();
    }

}

void DebugLogLayer::drawLayer()
{

    //  文字列が見やすいように背景に半透明の板を描画
    ogl::depthFunc(GL_ALWAYS);
    ogl::disable(GL_LIGHTING);
    ogl::enable(GL_BLEND);
    Color bg_color = Color(0, 0, 0, 80);
    drawRectangle(
        Vec2(0, 0),
        Vec2(glue::getScreenWidth(), glue::getScreenHeight()),
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


}   // namespace dbg
}   // namespace t3