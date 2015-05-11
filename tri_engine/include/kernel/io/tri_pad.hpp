/**
    @file tri_pad.hpp
    ゲームパッド.
*/

#ifndef TRI_PAD_HPP_INCLUDED
#define TRI_PAD_HPP_INCLUDED

//  include
#include "util/tri_uncopyable.hpp"
#include "base/tri_std.hpp"
#include "base/tri_types.hpp"

namespace t3 {

///
/// パッド
class Pad 
    : private Uncopyable
{
public:
    ///
    /// ボタン定義
    enum ButtonID{
        BUTTON_A        = 1 << 0,
        BUTTON_B        = 1 << 1,
        BUTTON_X        = 1 << 2,
        BUTTON_Y        = 1 << 3,
        
        BUTTON_L        = 1 << 5,
        BUTTON_R        = 1 << 6,
        
        BUTTON_UP       = 1 << 10,
        BUTTON_DOWN     = 1 << 11,
        BUTTON_RIGHT    = 1 << 12,
        BUTTON_LEFT     = 1 << 13,
        
        BUTTON_OPTION1  = 1 << 15,
        BUTTON_OPTION2  = 1 << 16,
        BUTTON_HOME     = 1 << 17,
        
        MAX_NORMAL_BUTTON_ID = 13,
        
        DEBUG_BUTTON_1  = 1 << 22,
        DEBUG_BUTTON_2  = 1 << 23,
        DEBUG_BUTTON_3  = 1 << 24,
        
        MAX_DEBUG_BUTTON_ID = 3,
        
        MAX_BUTTON_ID = MAX_NORMAL_BUTTON_ID + MAX_DEBUG_BUTTON_ID,
    };
    
public:
    ///
    /// コンストラクタ
    Pad();
    
    ///
    /// デストラクタ
    ~Pad();

public:
    ///
    /// 入力情報更新
    void updatePad( uint32_t current_frame_data, tick_t delta_time );
    
    ///
    /// トリガー判定
    bool isTrigger( uint32_t button ) const {
        return ( trigger_ & button ) != 0;
    }
    
    ///
    /// プレス判定
    bool isPress( uint32_t button ) const {
        return ( (last_frame_data_ & button) == button );
    }
    
    ///
    /// リリース判定
    bool isRelease( uint32_t button ) const {
        return ( release_ & button ) != 0;
    }

    ///
    /// リピート判定
    bool isRepeat( uint32_t button ) const {
        return ( repeat_ & button ) != 0;
    }
    
    
    ///
    /// トリガービットを取得
    uint32_t getTriggerBits() const {
        return trigger_;
    }
    
    ///
    /// プレスビットを取得
    uint32_t getPressBits() const {
        return last_frame_data_;
    }
    
    ///
    /// リリースビットを取得
    uint32_t getReleaseBits() const {
        return release_;
    }
    
    ///
    /// リピートビットを取得
    uint32_t getRepeatBits() const {
        return repeat_;
    }

private:
    ///
    /// リピートを更新
    void updateRepeat( tick_t delta_time );
    
private:
    ///
    /// 直前のフレームでのプレスデータ
    uint32_t last_frame_data_;
    
    ///
    /// トリガ入力ビット
    uint32_t trigger_;
    
    ///
    /// リリース入力ビット
    uint32_t release_;
    
    ///
    /// リピート入力ビット
    uint32_t repeat_;
    
    ///
    /// リピート開始フレーム
    float repeat_start_time_;
    
    ///
    /// リピート判定のインターバル
    float repeat_interval_;
    
    ///
    /// プレス入力時間
    float pressed_time_;
};
  

}   // namespace t3

#endif // TRI_PAD_HPP_INCLUDED

