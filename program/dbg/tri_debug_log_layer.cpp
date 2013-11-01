#include "tri_debug_log_layer.hpp"
#include "../gfx/tri_color.hpp"
#include "tri_print.hpp"


namespace t3 {
inline namespace dbg {

constexpr int DEBUG_LOG_LINE = 43;

DebugLogLayer::DebugLogLayer()
    : debug_log_buffer_()
    , log_show_offset_(0)
{

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
    if (debug_log_buffer_.getStringCount() == 0) {
        //  一つも登録されてないので即抜け
        return;
    }

    int str_idx = getLogShowLineIndex();
    
    int line = str_idx;
    if (line > DEBUG_LOG_LINE) {
        line = DEBUG_LOG_LINE;
    }

    //  下から順番にログを書く
    for (; line >= 0; --line) {
        DebugStringLayer::writeString(
            30,
            line * 16,
            Color::white().getRGBA(),
            debug_log_buffer_.getString(str_idx)
        );
        --str_idx;
    }
}

int DebugLogLayer::getLogShowLineIndex() const {

    int index = debug_log_buffer_.getStringCount() -1 + log_show_offset_;
    
    return index;
}



}   // namespace dbg
}   // namespace t3