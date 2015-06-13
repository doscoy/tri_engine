/**
    @file tri_debug_log_buffer.hpp
    デバッグログバッファ.
*/

#ifndef TRI_DEBUG_LOG_BUFFER_HPP_INCLUDED
#define TRI_DEBUG_LOG_BUFFER_HPP_INCLUDED

//  include 
#include "core_config.hpp"
#include "../utility/tri_uncopyable.hpp"
#include <queue>

TRI_CORE_NS_BEGIN


//  定数
constexpr int DEBUG_LOG_BUFFER_SIZE = 2048;
constexpr int DEBUG_LOG_STRING_LENGTH = 80;

///
/// デバッグ用ログアイテム
struct DebugLogItem {
    char str_[DEBUG_LOG_STRING_LENGTH];
};

///
/// ログを溜めるバッファ
class DebugLogBuffer
    : private Uncopyable
{
public:
    ///
    /// コンストラクタ
    DebugLogBuffer();

    ///
    /// デストラクタ
    ~DebugLogBuffer();

public:
    ///
    /// ログ追加
    void addString(
        const char* const str
    );
    
    ///
    /// ログ数カウント
    size_t getStringCount() const {
        return buffer_.size();
    }
    
    ///
    /// 文字列取得
    const char* getString(
        int index
    ) {
        return buffer_.at(index).str_;
    }
    
    
private:
    std::deque<DebugLogItem> buffer_;   ///< ログ用バッファ
};


TRI_CORE_NS_END




#endif  // TRI_DEBUG_LOG_BUFFER_HPP_INCLUDED
