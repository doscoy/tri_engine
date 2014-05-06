//
//  ViewController.m
//  tri_sandbox_ios
//
//  Created by KANI Tetsuro on 2014/02/25.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#import "ViewController.hpp"

#include "base/tri_application.hpp"
#include "platform/platform.hpp"
#include "AppDelegate.hpp"
#include "dbg/tri_trace.hpp"

#import <CoreMotion/CoreMotion.h>

#import "GADBannerView.h"

int iosMain(int argc, char** argv) {
    
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


GADBannerView* banner_view_ = nullptr;

@interface ViewController () {

}
@property (strong, nonatomic) EAGLContext *context;

@end

@implementation ViewController

#define MY_BANNER_UNIT_ID  @"ca-app-pub-3998377149074428/6255650398"

- (void)setupAdView
{
    //  画面上部に標準サイズのビューを作成
    banner_view_ = [[GADBannerView alloc] initWithAdSize: kGADAdSizeSmartBannerPortrait];
    
    //  広告ユニットIDを指定
    banner_view_.adUnitID = MY_BANNER_UNIT_ID;
    
    //  ユーザーに広告を表示した場所にあとで復元するUIViewControllerをランタイムに知らせて
    // ビュー階層に追加する
    banner_view_.rootViewController = self;
    [self.view addSubview:banner_view_];
    
    GADRequest* ad_req = [GADRequest request];
    ad_req.testDevices = [NSArray arrayWithObjects:
        GAD_SIMULATOR_ID,
        @"6777c2466ac06c61cf44cc1b3fd9a7648713844d",  // test iphone
        nil
    ];
    [banner_view_ loadRequest:ad_req];
    
    banner_view_.hidden = YES;
}





- (void)viewDidLoad
{
    [super viewDidLoad];
    
    
    [self setupAdView];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    //  FPS設定
    self.preferredFramesPerSecond = 60;
    
    [EAGLContext setCurrentContext:self.context];
    
    
    //  加速度センサー
    motion_manager_ = [[CMMotionManager alloc] init];
    
    if (motion_manager_.accelerometerAvailable) {
        //  加速度センサー更新タイミング
        motion_manager_.accelerometerUpdateInterval = 1.0f / 30.0f;
    
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
