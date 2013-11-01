
#ifndef tri_sandbox_osx_tri_debug_log_buffer_hpp
#define tri_sandbox_osx_tri_debug_log_buffer_hpp

#include "../util/tri_uncopyable.hpp"
#include <queue>


namespace t3 {
inline namespace dbg {


constexpr int DEBUG_LOG_BUFFER_SIZE = 2048;
constexpr int DEBUG_LOG_STRING_LENGTH = 80;
struct DebugLogItem
{
    char str_[DEBUG_LOG_STRING_LENGTH];
};


class DebugLogBuffer
    : private Uncopyable
{
public:
    DebugLogBuffer();
    ~DebugLogBuffer();

public:
    void addString(
        const char* const str
    );
    
    size_t getStringCount() const {
        return buffer_.size();
    }
    
    const char* getString(
        int index
    ) {
        return buffer_.at(index).str_;
    }
    
    
private:
    std::deque<DebugLogItem> buffer_;
};


}   // namespace dbg
}   // namespace t3




#endif
