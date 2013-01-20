#include "tri_debug_string_buffer.hpp"
#include "../gfx/tri_color.hpp"
#include "tri_print.hpp"
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdarg.h>
#include "../platform/platform.hpp"


extern void beginPrint( const float w, const float h );
extern void endPrint();
extern void debugFontPrint(const char c, const int x, const int y, const t3::u_int color, const int font_pixel_size);


namespace  {

void drawString(
    int x,
    int y,
    t3::u_int color,
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
    const u_int color,
    const char* const str
){
    debug_string_item_t& item = buffer_[size_];

    item.color = color;
    item.x = x;
    item.y = y;
    std::strncpy( item.str, str, DEBUG_STRING_ITEM_STR_SIZE );
    
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
        const debug_string_item_t& str_item = buffer_[item_idx];
        drawString(
            str_item.x,
            str_item.y,
            str_item.color,
            str_item.str
        );
    }
    
    endPrint();
}




}   // inline namespace dbg
}   // namespace t3

