//
//  ViewController.m
//  tri_sandbox_ios
//
//  Created by KANI Tetsuro on 2014/02/25.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#import "ViewController.h"


#include "base/tri_application.hpp"
#include "platform/platform.hpp"
#include "AppDelegate.h"
#include "dbg/tri_trace.hpp"

#import <CoreMotion/CoreMotion.h>

t3::Application* app_ = nullptr;


int iosMain(int argc, char** argv, t3::Application* app) {
    app_ = app;
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }

}

float screen_scale_ = 1.0f;
float screen_x_ = 0;
float screen_y_ = 0;

extern t3::Application* app_;
extern t3::platform::PointingData point_data_[4];
extern t3::platform::AccelerometerData acc_data_[4];

CMMotionManager* motion_manager_ = nullptr;


@interface ViewController () {

}
@property (strong, nonatomic) EAGLContext *context;

@end

@implementation ViewController



- (void)viewDidLoad
{

    [super viewDidLoad];
    

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat16;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGB565;
    
    //  FPS設定
    self.preferredFramesPerSecond = 60;
    
    [EAGLContext setCurrentContext:self.context];
    
    
    //  加速度センサー
    motion_manager_ = [[CMMotionManager alloc] init];
    
    if (motion_manager_.accelerometerAvailable) {
        //  加速度センサー更新タイミング
        motion_manager_.accelerometerUpdateInterval = 1.0f / 15.0f;
    
        // プル型の更新で取得
        [motion_manager_ startAccelerometerUpdates];
    
    }
    
    
    // 各機種で内部の座標系を統一する
    screen_scale_ = [UIScreen mainScreen].scale;

    CGRect bounds = [UIScreen mainScreen].bounds;
    screen_x_ = bounds.size.width * screen_scale_;
    screen_y_ = bounds.size.height * screen_scale_;
    
    t3::initializeTriEngine(screen_x_, screen_y_, "ios");
    app_->initializeApplication();
}





- (void)dealloc
{
    if (motion_manager_.accelerometerActive) {
        [motion_manager_ stopAccelerometerUpdates];
    }
    
    app_->terminateApplication();
    
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

// 画面に指を一本以上タッチしたときに実行されるメソッド
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = true;
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    float touch_x = location.x * screen_scale_;
    float touch_y = location.y * screen_scale_;
    float pos_x = touch_x - (screen_x_ / 2);
    float pos_y = -touch_y + (screen_y_ / 2);
    point_data_[0].x_ = pos_x;
    point_data_[0].y_ = pos_y;
}

// 画面に触れている指が一本以上移動したときに実行されるメソッド
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = true;
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    float touch_x = location.x * screen_scale_;
    float touch_y = location.y * screen_scale_;
    float pos_x = touch_x - (screen_x_ / 2);
    float pos_y = -touch_y + (screen_y_ / 2);
    point_data_[0].x_ = pos_x;
    point_data_[0].y_ = pos_y;

}

// 指を一本以上画面から離したときに実行されるメソッド
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = false;
}

// システムイベントがタッチイベントをキャンセルしたときに実行されるメソッド
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = false;
}


- (void)updateAccele
{
    CMAccelerometerData* newest_accel = motion_manager_.accelerometerData;

    acc_data_[0].x_ = newest_accel.acceleration.x;
    acc_data_[0].y_ = newest_accel.acceleration.y;
    acc_data_[0].z_ = newest_accel.acceleration.z;

}



#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    [self updateAccele];

    app_->updateApplication();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{

    app_->renderApplication();
}

#pragma mark -  OpenGL ES 2 shader compilation



@end
