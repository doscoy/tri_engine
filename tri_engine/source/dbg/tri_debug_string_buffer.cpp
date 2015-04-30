#include "dbg/tri_debug_string_buffer.hpp"
#include "gfx/tri_color.hpp"
#include "dbg/tri_print.hpp"
#include "kernel/tri_kernel.hpp"
#include "base/tri_director.hpp"

extern void beginPrint(const float w, const float h);
extern void endPrint();
extern void debugFontPrint(
    const char c,
    const int x,
    const int y,
    const t3::rgba32_t color,
    const int font_pixel_size
);


namespace  {

void drawString(
    const int x,
    const int y,
    const t3::rgba32_t color,
    const int size,
    const char* const str
){
    int font_size = size;
    int pitch = font_size - 2;
    int idx = 0;
    const char* c = str;
    while(*c){
        debugFontPrint( *c, x + idx * pitch, y, color, font_size );
        ++c;
        ++idx;
    }
}


}   // unname namespace



namespace t3 {

DebugStringBuffer::DebugStringBuffer()
    : size_( 0 )
{
    
}

DebugStringBuffer::~DebugStringBuffer()
{
    
}


void DebugStringBuffer::addString(
    const int x,
    const int y,
    const rgba32_t color,
    const int size,
    const char* const str
){
    if (size_ >= buffer_.size()) {
        return;
    }

    DebugStringItem& item = buffer_.at(size_);

    item.color_ = color;
    item.x_ = x;
    item.y_ = y;
    item.size_ = size;
    std::strncpy( item.str_, str, DEBUG_STRING_ITEM_STR_SIZE );
    
    ++size_;
}


void DebugStringBuffer::clearBuffer()
{
    size_ = 0;
}

void DebugStringBuffer::drawStrings()
{
    Director& gs = Director::instance();
    beginPrint(gs.screenSize().x_, gs.screenSize().y_);
 
    
    for (int item_idx = 0; item_idx < size_; ++item_idx ) {
        const DebugStringItem& str_item = buffer_[item_idx];
        drawString(
            str_item.x_,
            str_item.y_,
            str_item.color_,
            str_item.size_,
            str_item.str_
        );
    }
    
    endPrint();
}


}   // namespace t3

