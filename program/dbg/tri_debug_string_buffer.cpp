#include "tri_debug_string_buffer.hpp"
#include "../gfx/tri_color.hpp"
#include "tri_print.hpp"
#include <GLUT/glut.h>
#include <stdio.h>
#include <cstdarg>
#include "../platform/platform.hpp"


extern void beginPrint( const float w, const float h );
extern void endPrint();
extern void debugFontPrint(const char c, const int x, const int y, const uint32_t color, const int font_pixel_size);


namespace  {

void drawString(
    int x,
    int y,
    uint32_t color,
    const char* const str
){
    int font_size = 16;
    int pitch = font_size - 3;
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
inline namespace dbg {

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
    const char* const str
){
    DebugStringItem& item = buffer_.at(size_);

    item.color_ = color;
    item.x_ = x;
    item.y_ = y;
    std::strncpy( item.str_, str, DEBUG_STRING_ITEM_STR_SIZE );
    
    ++size_;
}


void DebugStringBuffer::clearBuffer()
{
    size_ = 0;
}

void DebugStringBuffer::drawStrings()
{
    beginPrint( glue::getScreenWidth(), glue::getScreenHeight() );
    
    for (int item_idx = 0; item_idx < size_; ++item_idx ) {
        const DebugStringItem& str_item = buffer_[item_idx];
        drawString(
            str_item.x_,
            str_item.y_,
            str_item.color_,
            str_item.str_
        );
    }
    
    endPrint();
}




}   // inline namespace dbg
}   // namespace t3

