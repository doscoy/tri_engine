#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#import <CoreFoundation/CoreFoundation.h>

#include "platform_accelerometer.hpp"

@interface AccelerometerDispatcher : NSObject<UIAccelerometerDelegate>
{
    t3::platform::AccelerometerData acc_data_[4];
    CMMotionManager* motion_manager_;
}

- (id) init;
- (void) setAccelerometerEnabled: (bool) isEnabled;
- (void) setAccelerometerInterval: (float) interval;
- (void) copyValue:(t3::platform::AccelerometerData*) v;
@end


@implementation AccelerometerDispatcher


- (id) init {
    if (self = [super init]) {
        motion_manager_ = [[CMMotionManager alloc] init];
    }
    return self;
}


- (void) setAccelerometerEnabled:(bool)isEnabled {
    if (isEnabled) {
        [motion_manager_ startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
            [self accelerometer:accelerometerData];
        }];
    } else {
        [motion_manager_ stopAccelerometerUpdates];
    }
}

- (void) setAccelerometerInterval:(float)interval {
    motion_manager_.accelerometerUpdateInterval = interval;
}

- (void) accelerometer:(CMAccelerometerData *)data {
    acc_data_[0].x_ = data.acceleration.x;
    acc_data_[0].y_ = data.acceleration.x;
    acc_data_[0].z_ = data.acceleration.x;
}

- (void) copyValue:(t3::platform::AccelerometerData*) v {
    *v = acc_data_[0];
}

@end


namespace t3 {
inline namespace platform {

AccelerometerDispatcher* acc_;

void platformAccelerometerInit() {
    acc_ = [[AccelerometerDispatcher alloc] init];
}

void platformAccelerometerEnable(bool flag) {
    [acc_ setAccelerometerEnabled:flag];
}

void platformAccelerometerInterval(float interval) {
    [acc_ setAccelerometerInterval:interval];
}



void platformAccelerometer(
    int no,
    AccelerometerData* data
) {

    [acc_ copyValue:data];
}


}
}