//
//  platform_accelerometer.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/11/12.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef CROSS_ACCELEROMETER_HPP_INCLUDED
#define CROSS_ACCELEROMETER_HPP_INCLUDED



namespace cross {




struct AccelerometerData {
    AccelerometerData()
        : x_(0)
        , y_(0)
        , z_(0)
    {
    }

    float x_;
    float y_;
    float z_;
};


void accelerometerInit();

void accelerometerEnable(bool flag);

void accelerometerInterval(float interval);

void accelerometerRead(
    int no,
    AccelerometerData* data
);


}   //  namespace cross

#endif  // CROSS_ACCELEROMETER_HPP_INCLUDED
