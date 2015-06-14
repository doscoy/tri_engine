#include "core/debug/tri_debug_string_buffer.hpp"
#include "core/graphics/tri_color.hpp"
#include "core/debug/tri_print.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/base/tri_director.hpp"



TRI_CORE_NS_BEGIN


DebugStringBuffer::DebugStringBuffer()
    : buffer_()
    , size_(0)
    , writer_()
{
    
}

DebugStringBuffer::~DebugStringBuffer()
{
    
}


void DebugStringBuffer::addString(
    const float x,
    const float y,
    const rgba32_t color,
    const int size,
    const char* const str
){
    if (size_ >= buffer_.size()) {
        return;
    }

    DebugStringItem& item = buffer_.at(size_);

    item.color_ = color;
    item.x_ = static_cast<short>(x);
    item.y_ = static_cast<short>(y);
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
    auto& d = Director::instance();
    writer_.beginPrint(d.screenSize().x_, d.screenSize().y_);
 
    
    for (int item_idx = 0; item_idx < size_; ++item_idx ) {
        const DebugStringItem& str_item = buffer_[item_idx];
        writer_.print(
            str_item.str_,
            str_item.x_,
            str_item.y_,
            str_item.color_,
            str_item.size_
        );
    }
    
    writer_.endPrint();
}


TRI_CORE_NS_END

