/**
    @file tri_pad.hpp
    ゲームパッド.
*/

#ifndef TRI_PAD_HPP_INCLUDED
#define TRI_PAD_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/base/tri_std.hpp"
#include "core/base/tri_types.hpp"
#include "cross/cross_sdk.hpp"
#include "core/math/tri_vec2.hpp"

TRI_CORE_NS_BEGIN


///
/// パッド
class Pad 
    : private Uncopyable
{
public:
    ///
    /// ボタン定義
    enum ButtonID{
        BUTTON_A        = cross::PAD_BUTTON_A,
        BUTTON_B        = cross::PAD_BUTTON_B,
        BUTTON_X        = cross::PAD_BUTTON_X,
        BUTTON_Y        = cross::PAD_BUTTON_Y,
        
        BUTTON_L        = cross::PAD_BUTTON_L,
        BUTTON_R        = cross::PAD_BUTTON_R,
        
        BUTTON_UP       = cross::PAD_BUTTON_UP,
        BUTTON_DOWN     = cross::PAD_BUTTON_DOWN,
        BUTTON_RIGHT    = cross::PAD_BUTTON_RIGHT,
        BUTTON_LEFT     = cross::PAD_BUTTON_LEFT,
        
        BUTTON_OPTION1  = cross::PAD_BUTTON_OPTION1,
        BUTTON_OPTION2  = cross::PAD_BUTTON_OPTION2,
        BUTTON_HOME     = cross::PAD_BUTTON_HOME,
        
        MAX_NORMAL_BUTTON_ID = 13,
        
        DEBUG_BUTTON_1  = cross::PAD_BUTTON_DEBUG1,
        DEBUG_BUTTON_2  = cross::PAD_BUTTON_DEBUG2,
        DEBUG_BUTTON_3  = cross::PAD_BUTTON_DEBUG3,
        
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
    void updatePad(const cross::GamePadData& paddata, tick_t delta_time);
    
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

    float getLTrigger() const {
        return l_trigger_;
    }
    
    float getRTrigger() const {
        return r_trigger_;
    }
    
    const Vec2& getLeftStick() const {
        return left_stick_;
    }
    
    const Vec2& getRightStick() const {
        return right_stick_;
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
    
    Vec2 left_stick_;
    Vec2 right_stick_;
    
    float l_trigger_;
    float r_trigger_;
};
  

TRI_CORE_NS_END

#endif // TRI_PAD_HPP_INCLUDED

