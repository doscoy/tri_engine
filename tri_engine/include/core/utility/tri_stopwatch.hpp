/**
    @file tri_stopwatch.hpp
    ストップウォッチ.
*/
#ifndef TRI_STOPWATCH_HPP_INCLUDED
#define TRI_STOPWATCH_HPP_INCLUDED


#include <chrono>
#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


///
/// タイム型
typedef std::chrono::time_point<std::chrono::steady_clock> Time;

///
/// システムタイム取得
inline Time getSystemTime(){
    return std::chrono::high_resolution_clock::now();
}

///
/// ストップウォッチ
class Stopwatch {
public:
    ///
    /// 計測開始
    void start(){
        start_time_ = getSystemTime();
    }

    ///
    /// 計測終了
    void end(){
        end_time_ = getSystemTime();
        last_start_time_ = start_time_;
    }

    ///
    /// インターバル値
    /// @return 秒
    float interval() const {
        auto v = std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - last_start_time_);
        return (float)v.count() / (float)1000000;
    }

    
private:
    ///
    /// 開始時間
    Time start_time_;
    
    ///
    /// 最後に開始した時間
    Time last_start_time_;
    
    ///
    /// 終了タイム
    Time end_time_;
};


TRI_CORE_NS_END


#endif // TRI_STOPWATCH_HPP_INCLUDED