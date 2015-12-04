////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

///
/// 加速度センサの取得 iOS

//  include
#include "cross_config.hpp"
#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#include "cross_accelerometer.hpp"




///
/// 加速度センサ情報取得用インターフェース
@interface AccelerometerDispatcher : NSObject<UIAccelerometerDelegate>
{
    t3::cross::AccelerometerData acc_data_[4];
    CMMotionManager* motion_manager_;
}

- (id) init;
- (void) setAccelerometerEnabled: (bool) isEnabled;
- (void) setAccelerometerInterval: (float) interval;
- (void) copyValue:(t3::cross::AccelerometerData*) v;
@end


@implementation AccelerometerDispatcher


///
/// 初期化
- (id) init {
    if (self = [super init]) {
        motion_manager_ = [[CMMotionManager alloc] init];
    }
    return self;
}

///
/// 有効化
- (void) setAccelerometerEnabled:(bool)isEnabled {
    if (isEnabled) {
        [motion_manager_ startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
            [self accelerometer:accelerometerData];
        }];
    } else {
        [motion_manager_ stopAccelerometerUpdates];
    }
}

///
/// インターバル値設定
- (void) setAccelerometerInterval:(float)interval {
    motion_manager_.accelerometerUpdateInterval = interval;
}

///
/// データ取得
- (void) accelerometer:(CMAccelerometerData *)data {
    acc_data_[0].x_ = data.acceleration.x;
    acc_data_[0].y_ = data.acceleration.x;
    acc_data_[0].z_ = data.acceleration.x;
}

///
/// 数値をコピー
- (void) copyValue:(t3::cross::AccelerometerData*) v {
    *v = acc_data_[0];
}

@end


CROSS_NS_BEGIN

AccelerometerDispatcher* acc_;

///
/// 加速度センサの初期化
void accelerometerInit() {
    acc_ = [[AccelerometerDispatcher alloc] init];
}

///
/// 加速度センサ有効化
void accelerometerEnable(bool flag) {
    [acc_ setAccelerometerEnabled:flag];
}

///
/// 加速度センサのインターバル設定
void accelerometerInterval(float interval) {
    [acc_ setAccelerometerInterval:interval];
}

///
/// 加速度センサ値を取得
void accelerometerRead(
    int no,
    AccelerometerData* data
) {
    [acc_ copyValue:data];
}

CROSS_NS_END

