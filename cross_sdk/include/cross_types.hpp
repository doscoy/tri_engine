#ifndef PLATFORM_TYPES_HPP_INCLUDED
#define PLATFORM_TYPES_HPP_INCLUDED

//  include
#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>



namespace cross {

///
/// プラットフォームから取得するパッドデータ
struct GamePadData {
    ///
    /// コンストラクタ
    GamePadData()
        : button_data_(0)
        , stick1x_(0)
        , stick1y_(0)
        , stick2x_(0)
        , stick2y_(0)
        , trigger_l_(0)
        , trigger_r_(0)
    {}
    
    ///
    ///
    uint32_t buttonData() const {
        return button_data_;
    }
    
    
    ///
    /// データリセット
    void clearData() {
        button_data_ = 0;
        stick1x_ = 0;
        stick1y_ = 0;
        stick2x_ = 0;
        stick2y_ = 0;
        trigger_l_ = 0;
        trigger_r_ = 0;
    }


    uint32_t button_data_;  ///< ボタンデータ
    float stick1x_;         ///< スティック1の横方向値
    float stick1y_;         ///< スティック1の縦方向値
    float stick2x_;         ///< スティック2の横方向値
    float stick2y_;         ///< スティック2の縦方向値
    float trigger_l_;       ///< Lトリガの押し込み量
    float trigger_r_;       ///< Rトリガの押し込み量
    
};


///
///  プラットフォームから取得するポインティングデータ.
/// マウス、タッチパネル等
struct PointingData {

    ///
    ///
    PointingData()
        : x_(0.0f)
        , y_(0.0f)
        , hit_(false)
        , pointing_count_(0)
    {}
    
    ///
    ///
    int getPointingCount() const {
        return pointing_count_;
    }
    
    ///
    ///
    void clearData() {
        x_ = 0;
        y_ = 0;
        hit_ = false;
    }

    float x_;       ///< x座標
    float y_;       ///< y座標
    bool hit_;      ///< 触ってる状態
    int pointing_count_;    ///< ポインティングしてる数
    
};



}   // namespace cross

#endif // PLATFORM_TYPES_HPP_INCLUDED
