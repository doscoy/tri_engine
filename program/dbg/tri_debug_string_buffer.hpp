
#ifndef TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED
#define TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED

#include "../base/tri_types.hpp"
#include "../util/tri_uncopyable.hpp"
#include <array>


namespace t3 {


inline namespace dbg {

constexpr int DEBUG_STRING_ITEM_STR_SIZE = 100;

struct DebugStringItem
{
    uint32_t color_;
    short x_;
    short y_;
    char str_[DEBUG_STRING_ITEM_STR_SIZE];
};


class DebugStringBuffer
    : private Uncopyable
{
public:
    DebugStringBuffer();
    ~DebugStringBuffer();
    
    
public:
    void addString(
        int x,
        int y,
        const uint32_t color,
        const char* const str
    );
    
    void clearBuffer();
    void drawStrings();
    
private:
    std::array<DebugStringItem, 100> buffer_;
    int size_;

};




}   // inline namespace dbg
}   // namespace t3




#endif // TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED