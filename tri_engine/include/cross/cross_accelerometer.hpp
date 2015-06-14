/**
    @file cross_accelerometer.hpp
    デバイスの加速度センサ.
*/


#ifndef CROSS_ACCELEROMETER_HPP_INCLUDED
#define CROSS_ACCELEROMETER_HPP_INCLUDED

#include "cross_config.hpp"


CROSS_NS_BEGIN



///
/// 加速度センサー
struct AccelerometerData {
    AccelerometerData()
        : x_(0)
        , y_(0)
        , z_(0)
    {}

    float x_;   ///< x
    float y_;   ///< y
    float z_;   ///< z
};


///
/// 加速度センサーの初期化
void accelerometerInit();

///
/// 加速度センサーの有効化
void accelerometerEnable(bool flag);

///
/// 加速度センサーの検知インターバル
void accelerometerInterval(float interval);

///
/// 加速度センサーデータの取得
void accelerometerRead(
    int no,
    AccelerometerData* data
);


CROSS_NS_END

#endif  // CROSS_ACCELEROMETER_HPP_INCLUDED
