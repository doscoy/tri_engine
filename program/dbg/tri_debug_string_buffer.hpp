
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
    u_int color;
    short x;
    short y;
    char str[DEBUG_STRING_ITEM_STR_SIZE];
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
        const u_int color,
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