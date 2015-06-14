/**
    @file tri_counter.hpp
    カウンタークラス定義.
*/

#ifndef TRI_COUNTER_HPP_INCLUDED
#define TRI_COUNTER_HPP_INCLUDED


#include "core/core_config.hpp"

TRI_CORE_NS_BEGIN


///
/// カウンタークラス
class Counter {
public:
    ///
    /// コンストラクタ
    Counter()
        : num_( 0 )
    {}
    
    
    ///
    /// 現在地
    int now() const {
        return num_;
    }
    
    ///
    /// カウントアップ
    void countup() {
        num_ += 1;
    }
    
    ///
    /// カウントダウン
    void countdown() {
        num_ -= 1;
    }
    
private:
    int num_;   ///< カウント値
};


extern Counter frame_counter_;

TRI_CORE_NS_END



#endif // TRI_COUNTER_HPP_INCLUDED