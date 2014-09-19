
#ifndef TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED
#define TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED

#include "base/tri_std.hpp"
#include "util/tri_uncopyable.hpp"


namespace t3 {


inline namespace dbg {

constexpr int DEBUG_STRING_ITEM_STR_SIZE = 95;

struct DebugStringItem
{
    uint32_t color_;
    short x_;
    short y_;
    char str_[DEBUG_STRING_ITEM_STR_SIZE];
    char size_;
};


class DebugStringBuffer
    : private Uncopyable
{
public:
    DebugStringBuffer();
    ~DebugStringBuffer();
    
    
public:
    void addString(
        const int x,
        const int y,
        const uint32_t color,
        const int size,
        const char* const str
    );
    
    void clearBuffer();
    void drawStrings();
    
private:
    Array<DebugStringItem, 300> buffer_;
    int size_;

};




}   // inline namespace dbg
}   // namespace t3




#endif // TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED