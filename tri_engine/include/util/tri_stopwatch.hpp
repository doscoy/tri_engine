/**
    @file tri_stopwatch.hpp
    ストップウォッチ.
*/
#ifndef TRI_STOPWATCH_HPP_INCLUDED
#define TRI_STOPWATCH_HPP_INCLUDED


#include <chrono>

namespace t3 {

    
//using Time = std::chrono::system_clock::time_point;

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
//    std::chrono::microseconds interval() const {
//        return std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - last_start_time_);
//    }

    ///
    /// インターバル値
	float interval() const {

		return 0.1f;
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


}   //  namespace t3


#endif // TRI_STOPWATCH_HPP_INCLUDED