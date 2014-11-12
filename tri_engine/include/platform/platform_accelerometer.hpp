//
//  platform_accelerometer.hpp
//  tri_engine
//
//  Created by KANI Tetsuro on 2014/11/12.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_engine_platform_accelerometer_hpp
#define tri_engine_platform_accelerometer_hpp



namespace t3 {
inline namespace platform {



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


void platformAccelerometerInit();

void platformAccelerometerEnable(bool flag);

void platformAccelerometerInterval(float interval);

void platformAccelerometer(
    int no,
    AccelerometerData* data
);


}
}

#endif
